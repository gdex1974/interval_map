#pragma once

#include <map>
#include <limits>

namespace nonstd
{
template<class Key, class Value>
class interval_map
{
public:
    explicit interval_map(const Value &val)
    {
        m_map.insert(std::make_pair(std::numeric_limits<Key>::lowest(), val));
    }

    explicit interval_map(Value &&val)
    {
        m_map.emplace(std::numeric_limits<Key>::lowest(), std::move(val));
    }

    interval_map(const Value &val, std::initializer_list<std::pair<Key, Value>> &&otherPoints) : interval_map(val)
    {
        for (auto point : otherPoints)
        {
            m_map.insert(std::move(point));
        }
    }

    interval_map(const Value &val, const std::initializer_list<std::pair<Key, Value>> &otherPoints) : interval_map(val)
    {
        for (const auto &point : otherPoints)
        {
            m_map.insert(point);
        }
    }

    // Returns number of mapped intervals
    std::size_t size() const
    {
        return m_map.size();
    }

    // assign value val to interval [keyBegin, keyEnd). Overwrite previous values in this interval.
    // If !( keyBegin < keyEnd ), this designates an empty interval, and assign do nothing.
    void assign(const Key &keyBegin, const Key &keyEnd, const Value &val)
    {
        if (keyBegin < keyEnd)
        {
            auto itEnd = --m_map.upper_bound(keyEnd); // point to initial value referable by keyEnd
            if (itEnd->second != val)                 // a check can the intervals be optimized.
            {
                if (itEnd->first < keyEnd)
                {
                    //keyEnd is not present into m_map
                    m_map.insert(itEnd, std::make_pair(keyEnd, itEnd->second));
                }
                else
                {
                    --itEnd; // otherwise the {keyEnd, val} pair will be removed later if applicable
                }
            }

            const auto itBegin = --m_map.upper_bound(keyBegin); // point to initial value referable by keyBegin
            while (itEnd != itBegin)
            {
                m_map.erase(itEnd--); // remove all intermediate intervals
            }

            // if the value by keyBegin is already val, we don't need to do anymore
            if (itBegin->second != val)
            {
                if (itBegin->first < keyBegin)
                {
                    m_map.insert(itBegin, std::make_pair(keyBegin, val)); // simplest case
                }
                else
                {
                    // we need to update an element at itBegin or remove it
                    if (auto it = itBegin; it != m_map.begin() && (--it)->second == val)
                    {
                        m_map.erase(itBegin); //intervals optimization
                    }
                    else
                    {
                        itBegin->second = val; // update the value by existing key
                    }
                }
            }
        }
    }

    // look-up of the value associated with key
    Value const &operator[](Key const &key) const
    {
        return (--m_map.upper_bound(key))->second;
    }

    bool operator==(const interval_map &rhs) const
    {
        return m_map == rhs.m_map;
    }

//private:
    std::map<Key, Value> m_map;
};
}
