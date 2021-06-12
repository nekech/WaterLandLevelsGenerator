#ifndef MCTS_NODE
#define MCTS_NODE

#include <memory>
#include "GameField.h"

namespace MCTS
{
	template<class T>
	using shared_ptr = std::shared_ptr<T>;

    struct GameResult
    {
        unsigned int WaterCount = 0;
        unsigned int LandCount = 0;
    };

	struct Node : public std::enable_shared_from_this<Node>
	{
		GameField field;

		Step step;

		CellType nodePlayerType;
		CellType nodeOpponentType;
        
        CellType playerType;

		int visitCount = 0;

		double winScore = 0;
        
        bool isTerminal = false;

		std::weak_ptr<Node> parent;

		std::list<shared_ptr<Node>> childs;

		Node(shared_ptr<Node> parent, const GameField& field, Step step, CellType nodePlayerType, CellType playerType);

		void ComputeChilds();

		GameResult RandomPlayout();

		shared_ptr<Node> GetChildWithBestWinScore();
        shared_ptr<Node> GetChildWithBestUCTScore(int totalVisitCount);
        shared_ptr<Node> GetChildWithBestUCTScore(int totalVisitCount, double bestScore, std::function<bool(double, double)> compareFunction);

		shared_ptr<Node> GetRandomChildNode();
        
        double GetUCTScore(int totalVisitCount);

		void UpdateWinScore(GameResult result);
	};
}

#endif // !MCTS_NODE
