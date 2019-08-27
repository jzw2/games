#include <string>
#include <vector>

class Move {
 public:
  virtual ~Move() {}
};

class Game {
 public:
  enum GameState {
                  PlayerOneWin ,
                  PlayerTwoWin,
                  Tie,
                  InProgress
  };
  GameState player;
  class BestMove {
  public:
    Move* move;
    GameState result;

  BestMove(Move* m, GameState r) : move(m), result(r) {

    }

  };
  virtual void startGame() = 0;
  virtual void print() = 0;
  virtual std::vector<Move*> getAllPossibleMoves() = 0;
  virtual GameState makeMove(Move& m) = 0;

  virtual void undo() = 0;

  virtual Move* convertUserInputToMove(std::string s) = 0;
  virtual ~Game() {}
  BestMove* bestMove();

private:
  void switchPlayer() {
    if (player == PlayerOneWin) {
      player = PlayerTwoWin;
    } else {
      player = PlayerOneWin;
    }
  }
  

};
