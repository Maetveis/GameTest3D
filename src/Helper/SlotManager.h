#ifndef SLOT_MANAGER_H
#define SLOT_MANAGER_H

#include <stack>

template<int Min, int Max>
class SlotManager
{
public:
	int Allocate()
	{
		if(deleted.empty())
		{
			if(contFreeStart <= Max)
			{
				return contFreeStart++;
			} else {
				Logger::Warning << "SlotManager Out of slots " << '\n';
				return -1000;
			}
		} else {
			int slot = deleted.top();
			deleted.pop();
			return slot;
		}
	}
	
	void Deallocate(int slot)
	{
		if(slot - contFreeStart == 1)
		{
			--contFreeStart;
		} else {
			deleted.push(slot);
		}
	}
private:
	int contFreeStart = Min;
	std::stack<int> deleted;
};

#endif //SLOT_MANAGER_H