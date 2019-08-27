#include "game.h"
#include <vector>

class TicTacToeMove : public Move {
public:
  int loc;

  TicTacToeMove(int i) {
    loc = i;
  }

  virtual ~TicTacToeMove() override {}
};
class Board : public Game {
  std::vector<char> board;
  std::vector<TicTacToeMove> moves;
  char currentPlayer;

  bool winHorizontal(char c);
  bool winVertical(char c);
  bool winDiagonal(char c);
  bool win(char c);
  void switchPlayer();
public:

  virtual void startGame() override;
  virtual void print() override;
  virtual std::vector<Move*> getAllPossibleMoves() override;
  virtual GameState makeMove(Move& m) override;

  virtual void undo() override;

  virtual Move* convertUserInputToMove(std::string s) override;
  virtual ~Board() override;
};



