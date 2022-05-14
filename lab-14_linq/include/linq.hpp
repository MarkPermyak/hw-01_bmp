#ifndef LINQ_H_
#define LINQ_H_

#include <utility>
#include <vector>
#include <iterator>

namespace linq {

	namespace impl {

		template<typename T, typename Iter>
		class range_enumerator;

		template<typename T>
		class drop_enumerator;

		template<typename T>
		class take_enumerator;

		template<typename T, typename U, typename F>
		class select_enumerator;


		template<typename T>
		class enumerator {
		public:
			virtual T operator *() = 0;

			virtual void operator ++() = 0;

			virtual explicit operator bool() = 0;

			auto drop(int count) {
				return drop_enumerator(*this, count);				
			}

			auto take(int count) {
				return take_enumerator(*this, count);
			}

		  	template<typename U = T, typename F>
			auto select(F func) {
				return select_enumerator<U, T, F>(*this, std::move(func));		
			}

			template<typename Iter>
			void copy_to(Iter it) {
				while (operator bool()) {
					*it++ = operator *();
					++*this;
				}
			}

			std::vector<T> to_vector() {
				std::vector<T> result;
				copy_to(std::back_inserter(result));
				return result;
			}
		};

		template<typename T, typename Iter>
		class range_enumerator : public enumerator<T> {
		public:
			range_enumerator(Iter begin, Iter end) : begin_(begin), end_(end) {}

			T operator *() override {
				return *begin_;				
			}

			void operator ++() override {
				++begin_;
			}

			explicit operator bool() override {
				return begin_ != end_;
			} 

		private:
			Iter begin_, end_;
		};

		template<typename T>
		class drop_enumerator : public enumerator<T> {
		public:
			drop_enumerator(enumerator<T> & parent, int count) : parent_(parent), to_skip_(count) {}

			T operator *() override {
				ensure_skip();
				return *parent_;				
			}

			void operator ++() override {
				ensure_skip();
				++parent_;
			}

			explicit operator bool() override {
				ensure_skip();
				return static_cast<bool>(parent_);
			}

		private:
			void ensure_skip() {
				while (to_skip_ > 0 && static_cast<bool>(parent_)) {
					--to_skip_;
					++parent_;
				}
			}

			enumerator<T> & parent_;
			int to_skip_;
		};

		template<typename T>
		class take_enumerator : public enumerator<T> {
		public:
			take_enumerator(enumerator<T> & parent, int count) : parent_(parent), to_take_(count) {}

			T operator *() override {
				return *parent_;				
			}

			void operator ++() override {
				++parent_;
				to_take_--;
			}

			explicit operator bool() override {
				return to_take_ > 0 && static_cast<bool>(parent_);
			}

		private:
			enumerator<T> & parent_;
			int to_take_;
		};

		template<typename T, typename U, typename F>
		class select_enumerator : public enumerator<T> {
		public:
			select_enumerator(enumerator<U> & parent, F func) : parent_(parent), func_(std::move(func)) {}

			T operator *() override {
				return func_(*parent_);	
			}

			void operator ++() override {
				++parent_;
			}

			explicit operator bool() override {
				return static_cast<bool>(parent_);
			}

		private:
			enumerator<U> & parent_;
			F func_;
		};

	} 

	template<typename T>
	auto from(T begin, T end) {
		return impl::range_enumerator<typename std::iterator_traits<T>::value_type, T>(begin, end);
	}

}

#endif
