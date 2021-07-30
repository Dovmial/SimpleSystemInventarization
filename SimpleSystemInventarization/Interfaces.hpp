#ifndef _INTERFACES_HPP_
#define _INTERFACES_HPP_

struct BaseInterface {
	virtual bool edit() = 0;
	virtual bool add() = 0;
	virtual bool remove() = 0;
	virtual bool move() = 0;
	//virtual void show() = 0;
	virtual bool find() = 0;
};
#endif // !_INTERFACES_HPP_
