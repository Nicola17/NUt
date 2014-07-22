#ifndef PROGRESS_REDUCTION_INL
#define PROGRESS_REDUCTION_INL

#if defined(_OPENMP)
	#include "omp.h"
#endif

#include "errors/invariants.h"
namespace nut{
	
	ProgressReduction::ProgressReduction(AbstractProgress* external_progress, unsigned int num_external_steps):
		external_progress_(external_progress),
		num_external_steps_(num_external_steps),
		num_internal_steps_(0),
		reduction_ratio_(0),
		last_emitted_step_(0),
		internal_steps_(0)
	{
	}
	void ProgressReduction::MakeAStep(){
		if(external_progress_ == nullptr)
			return;
#if defined(_OPENMP)
		#pragma omp critical
#endif
		{
			internal_steps_ += reduction_ratio_;
		}
		
#if defined(_OPENMP)
		if(omp_get_thread_num() != 0){
			return;
		}
#endif
		const double to_increment(internal_steps_ - last_emitted_step_);

		assert(to_increment >= 0);
		for(unsigned int i = 0; i < static_cast<unsigned int>(to_increment) && last_emitted_step_ <= num_external_steps_; ++i){
			external_progress_->MakeAStep();
			++last_emitted_step_;
		}
	}
	bool ProgressReduction::IsCanceled()const{
		return (external_progress_ != nullptr)?external_progress_->IsCanceled():false;
	}
	void ProgressReduction::Reset(){
		last_emitted_step_ = 0;
		num_internal_steps_ = 0;
		internal_steps_ = 0.;
	}
	void ProgressReduction::Finalize(){
		PRECONDITION(last_emitted_step_ <= num_external_steps_);
		if(external_progress_ == nullptr) 
			return;
		int final_steps (static_cast<int>(num_external_steps_-last_emitted_step_));
		assert(final_steps >= 0);
		for(int i = 0; i < final_steps; ++i){
			external_progress_->MakeAStep();
			++last_emitted_step_;
		}
		internal_steps_ = last_emitted_step_;
	}

	void ProgressReduction::set_num_external_steps(unsigned int steps){
		num_external_steps_ = steps;
		reduction_ratio_ =(num_internal_steps_!=0)?double(num_external_steps_)/num_internal_steps_:0;
	}
	void ProgressReduction::set_num_internal_steps(unsigned int steps){
		num_internal_steps_ = steps;
		reduction_ratio_ =(num_internal_steps_!=0)?double(num_external_steps_)/num_internal_steps_:0;
	}
	void ProgressReduction::set_external_progress(AbstractProgress* prg){
		external_progress_ = prg;
	}


	unsigned int ProgressReduction::num_external_steps()const{
		return num_external_steps_;
	}
	unsigned int ProgressReduction::num_internal_steps()const{
		return num_internal_steps_;
	}
	double ProgressReduction::reduction_ratio()const{
		return reduction_ratio_;
	}

	AbstractProgress* ProgressReduction::external_progress(){
		return external_progress_;
	}
	const AbstractProgress* ProgressReduction::external_progress()const{
		return external_progress_;
	}

}

#endif // PROGRESS_REDUCTION_INL