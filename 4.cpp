#include <iostream>
#include <queue>
#include <unordered_set>

using namespace std;

const string GOAL = "ABCDEFGHIJKLMNO#";

// Moves and their effects on index position
const int dRow[] = {-1, 1, 0, 0}; // UP, DOWN, LEFT, RIGHT
const int dCol[] = {0, 0, -1, 1};
const string MOVES[] = {"UP", "DOWN", "LEFT", "RIGHT"};

struct State
{
      string board;
      int blankPos;
      int cost;

      State(string b, int pos, int c) : board(b), blankPos(pos), cost(c) {}
};

// Helper function to swap characters and return a new board state
string swapTiles(const string &board, int pos1, int pos2)
{
      string newBoard = board;
      swap(newBoard[pos1], newBoard[pos2]);
      return newBoard;
}

// Breadth-First Search (BFS) to find the shortest path to goal
int bfs(string start)
{
      queue<State> q;
      unordered_set<string> visited;

      int blankPos = start.find('#');
      q.push(State(start, blankPos, 0));
      visited.insert(start);

      while (!q.empty())
      {
            State current = q.front();
            q.pop();

            // If the goal state is reached, return the cost
            if (current.board == GOAL)
                  return current.cost;

            int row = current.blankPos / 4;
            int col = current.blankPos % 4;

            // Try all 4 possible moves
            for (int i = 0; i < 4; i++)
            {
                  int newRow = row + dRow[i];
                  int newCol = col + dCol[i];

                  // Check if the move is within bounds
                  if (newRow >= 0 && newRow < 4 && newCol >= 0 && newCol < 4)
                  {
                        int newPos = newRow * 4 + newCol;
                        string newBoard = swapTiles(current.board, current.blankPos, newPos);

                        // If this state hasn't been visited, add it to the queue
                        if (visited.find(newBoard) == visited.end())
                        {
                              q.push(State(newBoard, newPos, current.cost + 1));
                              visited.insert(newBoard);
                        }
                  }
            }
      }
      return -1;
}

int main()
{
      string start;
      cin >> start;

      int result = bfs(start);
      cout << result << endl;

      return 0;
}
