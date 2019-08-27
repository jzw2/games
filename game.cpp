#include "game.h"
#include <iostream>

Game::BestMove* Game::bestMove() {
  auto currentPlayer = player;
  BestMove* bestMove = nullptr;
  //switchPlayer();
  auto moves = getAllPossibleMoves();
  for (auto& m : moves) {
    auto state = makeMove(*m);

    if (state == currentPlayer) {
      undo();
      bestMove = new BestMove(m, state);
      break;
    }

    if (state == Tie) {
      bestMove = new BestMove(m, state);
    } else if (state == InProgress) {
      auto opponentBestMove = this->bestMove();
      auto result = opponentBestMove->result;
      
      if (result == currentPlayer) {
        undo();
        bestMove = new BestMove(m, result);
        break;
      }

      if (bestMove) {
        //bestMove not null
        auto oldBestMoveResult = bestMove->result;
        if (oldBestMoveResult != Tie) { //stick with the old one if it is already a itie
          bestMove = new BestMove(m, result);
        }
      } else {
        bestMove = new BestMove(m, result);
      }

    } else {
      //loss
      if (bestMove == nullptr) {
        bestMove = new BestMove(m, state);
      }
    }


    undo();
  }
  //switchPlayer();

  for (auto ptr : moves) {
    if (ptr != bestMove->move) {
      delete ptr;
    }
  }

  return bestMove;
}

