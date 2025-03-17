#include "Exception.h"

template <class State>
class ProblemStatement{
	protected:
		State SOURCE, DESTINATION;
	public:
		ProblemStatement(State SOURCE, State DESTINATION): SOURCE(SOURCE), DESTINATION(DESTINATION) {}

		virtual vector<State> getAdjacent(State state) {
			throw NotImplementedException();
		}

};