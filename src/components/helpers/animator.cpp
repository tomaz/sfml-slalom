#include <algorithm>

#include "animator.hpp"

namespace tk
{
	using namespace tk::animator;

#pragma region Construction & destruction

	//-------------------------------------------------------------------------
	Animator::Animator(double time, Type type)
		: Updatable::Updatable{}
		, m_type{ type }
		, m_total{ time }
		, m_time{ 0.0 } {
		reset();
	}

#pragma endregion

#pragma region Setup

	//-------------------------------------------------------------------------
	void Animator::addCallbacksEvery(double diff, animator::Callback callback) {
		m_callbacks.clear();

		double progress = 0.0;
		while (progress <= 1.0) {
			addCallback(progress, callback);
			progress += diff;
		}
	}

	//-------------------------------------------------------------------------
	void Animator::addCallbacksCount(int count, animator::Callback callback) {
		m_callbacks.clear();

		if (count == 1) {
			addCallback(0.0, callback);
		} else if (count >= 2) {
			double diff = 1.0 / (double)(count - 1);
			addCallbacksEvery(diff, callback);
		}
	}

	//-------------------------------------------------------------------------
	void Animator::addCallback(double progress, animator::Callback callback) {
		// Delete existing.
		auto it = std::find_if(
			m_callbacks.begin(),
			m_callbacks.end(),
			[&](auto &data) { return data.progress == progress; }
		);

		if (it != m_callbacks.end()) {
			m_callbacks.erase(it);
		}

		// Add new (if provided).
		if (!callback) return;

		// Insert the progress to the vector.
		m_callbacks.emplace_back(animator::ProgressData{ progress, callback });

		// Always keep vector sorted by the progress value.
		std::sort(
			m_callbacks.begin(),
			m_callbacks.end(),
			[](auto &c1, auto &c2) { return c1.progress < c2.progress; }
		);

		// We need to reset so iterators will point to correct element.
		m_currentIndex = 0;
		m_current	   = m_callbacks.begin();
	}

	//-------------------------------------------------------------------------
	void Animator::removeCallback(double progress) {
		addCallback(progress, nullptr);
	}

#pragma endregion

#pragma region Changing status

	//-------------------------------------------------------------------------
	void Animator::start() {
		if (active()) return;
		setActive(true);
	}

	//-------------------------------------------------------------------------
	void Animator::stop(bool shouldReset) {
		if (!active()) return;
		setActive(false);
		if (shouldReset) reset();
	}

	//-------------------------------------------------------------------------
	void Animator::reset() {
		m_total		   = 0.0;
		m_time		   = 0.0;
		m_prefix	   = 1.0;
		m_currentIndex = 0;
		m_current	   = m_callbacks.begin();
	}

#pragma endregion

#pragma region Overrides

	//-------------------------------------------------------------------------
	bool Animator::onUpdate(double delta) {
		if (m_total <= 0) return false;

		// Remember current values before we (potentially) reset them.
		auto lastPrefix = m_prefix;

		// Increase time.
		m_time += delta * m_prefix;

		// Handle animation types.
		switch (m_type) {
			case Type::OneShot:
				if (m_time >= m_total) {
					m_time = m_total;
					setActive(false);
				}
				break;

			case Type::OneShotBounce:
				if (m_time >= m_total) {
					m_time	 = m_total;
					m_prefix = -1.0;
				} else if (m_time <= 0.0) {
					m_time = 0.0;
					setActive(false);
				}
				break;

			case Type::Repeating:
				if (m_time >= m_total) {
					m_time = 0.0;
				}
				break;

			case Type::RepeatingBounce:
				if (m_time >= m_total) {
					m_time	 = m_total;
					m_prefix = -1.0;
				} else if (m_time <= 0.0) {
					m_time	 = 0.0f;
					m_prefix = 1.0;
				}
				break;
		}

		// If we have progress to report, check if we reached it.
		if (m_nextProgress >= 0.0) {
			// Calculate current progress.
			auto progress = m_time / m_total;

			if (lastPrefix > 0 && progress >= m_nextProgress) {
				// We reached next progress when moving upwards. Notify caller.
				m_current->callback(m_current->progress);

				// Move to next index, if past the end, go backwards.
				if (++m_current == m_callbacks.end()) {
					m_current -= 2;
				}
			} else if (lastPrefix < 0 && progress <= m_nextProgress) {
				// We reached next progress when moving downwards. Notify caller.
				m_callbacks[m_currentIndex].callback(progress);

				// If already at start, move to next, otherwise previous.
				if (m_current == m_callbacks.begin()) {
					m_current++;
				} else {
					m_current--;
				}
			}

			m_currentIndex = std::distance(m_callbacks.begin(), m_current);
			m_nextProgress = m_current->progress;
		}

		return true;
	}

#pragma endregion

} // namespace tk
