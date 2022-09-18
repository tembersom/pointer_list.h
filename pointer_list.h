#ifndef List
#define list List

// List made to be used with Objects.

template<class TYPE>
class node
{
private:
	TYPE * _obj;
	node * _next;
	node * _prev;
public:
	node::node() {
		_next = 0;
		_prev = 0;
		_obj = new TYPE;
	}
	node::~node() {
		delete & _obj;
		delete _obj;
		delete _next;
		delete _prev;
	}

	TYPE * node::GetObj() { return _obj; }
	node * node::GetNext() { return _next; }
	node * node::GetPrev() { return _prev; }
	void node::SetObj(TYPE * _var) { _obj = _var; }
	void node::SetNext(node * _var) { _next = _var;	}
	void node::SetPrev(node * _var) { _prev = _var;	}
};

template<class TYPE>
class list
{
private:
	int size;
	node<TYPE> * _first;
	node<TYPE> * _last;
public:
	list::list()
	{
		size = 0;
		_first = 0;
		_last = 0;
	}
	list::~list()
	{
		if (size < 0) {
			node<TYPE> * _finder = _first;
			for (int r = 1; r <= size; r++) {
				_finder = _finder->GetNext();
				delete _finder->GetPrev();
			}
			delete _finder;
		}
		delete size;
	}

	void list::AddBot() { //Add Node before First
		node<TYPE> * _temp = new node<TYPE>;
		if (size <= 0) {
			_first = _temp;
			_last = _temp;
		} else {
			_first->SetPrev(_temp);
			_temp->SetNext(_first);
			_first = _temp;
		}
		size++;
	}
	void list::AddTop() { //Add Node after Last
		node<TYPE> * _temp = new node<TYPE>;
		if (size <= 0) {
			_first = _temp;
			_last = _temp;
		} else {
			_last->SetNext(_temp);
			_temp->SetPrev(_last);
			_last = _temp;
		}
		size++;
	}
	void list::AddMid(int pos) { //Add node before POS (position)
		node<TYPE> * _temp = new node<TYPE>;
		if (size <= 0) {
			_first = _temp;
			_last = _temp;
		} else if (pos <= 1) {
			_first->SetPrev(_temp);
			_temp->SetNext(_first);
			_first = _temp;
		} else if (pos > size) {
			_last->SetNext(_temp);
			_temp->SetPrev(_last);
			_last = _temp;
		}
		node<TYPE> * _finder = _first;
		if (pos <= size / 2) for (int r = 1; r < pos; r++) _finder = _finder->GetNext();
		else {
			_finder = _last;
			for (int r = pos; r < size; r++) _finder = _finder->GetPrev();
		}
		_temp->SetPrev(_finder->GetPrev());
		_finder->GetPrev()->SetNext(_temp);
		_temp->SetNext(_finder);
		_finder->SetPrev(_temp);
		size++;
	}

	node<TYPE> * list::PopBot() { // INCOMPLETE
		node<TYPE> * _temp = _first;
		_first->GetNext()->SetPrev(0);
		_first = _temp->GetNext();
		
		size--;
		return _temp;
	}

	node<TYPE> * list::GetPos(int pos) { //Search for pos and return node pointer
		if (pos <= 1) return _first;
		if (pos >= size) return _last;
		node<TYPE> * _finder = _first;
		if (pos <= size / 2) for (int r = 1; r < pos; r++) _finder = _finder->GetNext();
		else {
			_finder = _last;
			for (int r = pos; r < size; r++) _finder = _finder->GetPrev();
		}
		return _finder;
	}

	void list::Delete(int pos) {
		if (size > 0) {
			node<TYPE> * _finder = _first;
			if (pos <= size / 2) for (int r = 1; r < pos; r++) _finder = _finder->GetNext();
			else {
				_finder = _last;
				for (int r = pos; r < size; r++) _finder = _finder->GetPrev();
			}
			if (_finder->GetNext() != 0) {
				if (_finder->GetPrev() != 0) {
					_finder->GetNext()->SetPrev(_finder->GetPrev());
					_finder->GetPrev()->SetNext(_finder->GetNext());
				}
				else {
					_finder->GetNext()->SetPrev(0);
					_first = _finder->GetNext();
				}
			}
			else {
				if (_finder->GetPrev() != 0) {
					_finder->GetPrev()->SetNext(0);
					_last = _finder->GetPrev();
				}
				else {
					_first = 0;
					_last = 0;
				}
			}
			size--;
			delete _finder;
		}
	}

	node<TYPE> * list::GetFirst() { return _first; }
	node<TYPE> * list::GetLast() { return _last; }
	TYPE * list::GfObj() { return _first->GetObj(); } //Get First node object pointer
	TYPE * list::GlObj() { return _last->GetObj(); } // Get Last node object pointer
	TYPE * list::GpObj(int pos) { // Get POS (position) node object pointer
	if (pos <= 1) return _first->GetObj();
		if (pos >= size) return _last->GetObj();
		node<TYPE> * _finder = _first;
		if (pos <= size / 2) for (int r = 1; r < pos; r++) _finder = _finder->GetNext();
		else {
			_finder = _last;
			for (int r = pos; r < size; r++) _finder = _finder->GetPrev();
		}
		return _finder->GetObj();
	}
	int list::GetSize() { return size; }
};
#endif