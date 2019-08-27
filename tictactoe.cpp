#include "tictactoe.h"

#include <iostream>
#include <cstring>
#include <algorithm>

void Board::switchPlayer() {
  if (currentPlayer == 'X') {
    currentPlayer = 'O';
  } else {
    
    currentPlayer = 'X';
  }

  if (player == Game::GameState::PlayerOneWin) {
    player = Game::GameState::PlayerTwoWin;
  } else {
    player = Game::GameState::PlayerOneWin;
  }
  
}

bool Board::winHorizontal(char c) {
  for (int i = 0; i < 9; i+= 3) {
    bool same = true;
    for (int j = 0; j < 3; j++) {
      same = same && board[i + j] == c;
    }
    if (same) {
      return true;
    }
  }

  return false;
}
bool Board::winVertical(char c) {
  for (int i = 0; i < 3; i++) {
    bool same = true;
    for (int j = 0; j < 9; j+=3) {
      same = same && board[i + j] == c;
    }
    if (same) {
      return true;
    }
  }
  return false;
}
bool Board::winDiagonal(char c) {
  bool diag1 =
    c == board[0]
    && c == board[4]
    && c == board[8];
  bool diag2 =
    c == board[2]
    && c == board[4]
    && c == board[6];

  return diag1 || diag2;
}
bool Board::win(char c) {
  return winHorizontal(c) || winVertical(c) || winDiagonal(c);
}

void Board::startGame() {
  board = std::vector<char>(9, ' ');
  currentPlayer = 'X';
  player = Game::GameState::PlayerOneWin;
}

void Board::print() {
  std::cout << std::string(5,'-') << std::endl;
  for (int i = 0; i < 9; i+=3) {
    std::cout << "|" << std::string(board.begin() + i, board.begin() + i + 3) << "|" << std::endl;
  }
  std::cout << std::string(5,'-') << std::endl;
}
std::vector<Move*> Board::getAllPossibleMoves() {
  std::vector<Move*> ret;
  for (int i = 0; i < 9; i++) {
    if (board[i] == ' ') {
      ret.push_back(new TicTacToeMove(i));
    }
  }

  return ret;
}
Game::GameState Board::makeMove(Move& m) {
  TicTacToeMove& tttm = dynamic_cast<TicTacToeMove&>(m);
  moves.push_back(tttm);
  board[tttm.loc] = currentPlayer;
  switchPlayer();
  if (win('X')) {
    return Game::GameState::PlayerOneWin;
  }
  if (win('O')) {
    return Game::GameState::PlayerTwoWin;
  }
  if (std::find(board.begin(), board.end(), ' ') == board.end()) {
    return Game::GameState::Tie;
  }

  return Game::GameState::InProgress;
}

void Board::undo() {
  auto oldMove = moves.back();
  moves.pop_back();
  board[oldMove.loc] = ' ';
  switchPlayer();
}

Move* Board::convertUserInputToMove(std::string s) {
  int i = std::stoi(s);
  return new TicTacToeMove(i);
}
Board::~Board() {}


int main() {
  int location;
  Board b;
  b.startGame();
  // Game::BestMove* bestMove = b.bestMove();
  // Move* move = bestMove->move;

  // b.makeMove(*move);

  // b.print();
  while(std::cin >> location) {
    TicTacToeMove m(location);
    if (b.makeMove(m) != Game::GameState::InProgress) {
      break;
    }
    b.print();


    Game::BestMove* bestMove = b.bestMove();
    std::cout << "Finished thinking with result " << bestMove->result << std::endl;
    Move* move = bestMove->move;

    if (b.makeMove(*move) != Game::GameState::InProgress) {
      break;
    }

    b.print();
  }
  b.print();
}
