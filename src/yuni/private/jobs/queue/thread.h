#ifndef __YUNI_PRIVATE_JOBS_QUEUE_THREAD_H__
# define __YUNI_PRIVATE_JOBS_QUEUE_THREAD_H__

# include "../../../thread/thread.h"
# include "../../../job/queue/service.h"


namespace Yuni
{
namespace Private
{
namespace QueueService
{

	/*!
	** \brief A single thread for a queue service
	*/
	class YUNI_DECL QueueThread final : public Yuni::Thread::IThread
	{
	public:
		//! The most suitable smart pointer for the class
		typedef Yuni::Thread::IThread::Ptr::Promote<QueueThread>::Ptr Ptr;

	public:
		//! \name Constructor & Destructor
		//@{
		/*!
		** \brief Default Constructor
		*/
		explicit QueueThread(Yuni::Job::QueueService& scheduler);
		//! Destructor
		virtual ~QueueThread();
		//@}

		/*!
		** \brief Get the Job currently running
		*/
		Yuni::Job::IJob::Ptr currentJob() const;


	protected:
		/*!
		** \brief Implementation of the `onExecute` method to run the jobs from the waiting room
		*/
		virtual bool onExecute() final;

		/*!
		** \brief Implementation of the `onKill` method when the thread is killed without mercy
		*/
		virtual void onKill() final;


	private:
		//! The scheduler
		Yuni::Job::QueueService& pScheduler;
		//! The current job
		Yuni::Job::IJob::Ptr pJob;

	}; // class QueueThread






} // namespace QueueService
} // namespace Private
} // namespace Yuni

# include "thread.hxx"

#endif // __YUNI_PRIVATE_JOBS_QUEUE_THREAD_H__
