
template<typename Number>
class Tan
{
public:
	

	virtual bool is_selected () const = 0;
	virtual bool is_offset   () const = 0;

	const_iterator begin () const;
	const_iterator end   () const;

	iterator       begin ();
	iterator       end   ();

	
};

template<typename Number>
class Game
{

};
	
