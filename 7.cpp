#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>
#include <fstream>

using namespace std;

const string GOAL = "ABCDEFGHIJKLMNO#";
const int dRow[] = {-1, 1, 0, 0}; // UP, DOWN, LEFT, RIGHT
const int dCol[] = {0, 0, -1, 1};

// Precompute goal positions
int goalRow[256], goalCol[256];

struct State
{
      string board;
      int blankPos;
      int g, h;
      int nodesExpanded;

      State(string b, int pos, int cost, int expNodes, int heuristic)
          : board(b), blankPos(pos), g(cost), nodesExpanded(expNodes)
      {
            h = (heuristic == 1) ? misplacedTiles(b) : tileDistance(b);
      }

      int f() const
      {
            return g + h;
      }

      bool operator>(const State &other) const
      {
            return this->f() > other.f();
      }

      static int misplacedTiles(const string &b)
      {
            int count = 0;
            for (int i = 0; i < 16; i++)
            {
                  if (b[i] != GOAL[i] && b[i] != '#')
                  {
                        count++;
                  }
            }
            return count;
      }

      static int tileDistance(const string &b)
      {
            int distance = 0;
            for (int i = 0; i < 16; i++)
            {
                  char c = b[i];
                  if (c != '#' && c != GOAL[i])
                  {
                        int row = i / 4, col = i % 4;
                        distance += abs(row - goalRow[c]) + abs(col - goalCol[c]);
                  }
            }
            return distance;
      }
};

string swapTiles(const string &board, int pos1, int pos2)
{
      string newBoard = board;
      swap(newBoard[pos1], newBoard[pos2]);
      return newBoard;
}

// BFS Algorithm
pair<int, int> bfs(string start)
{
      queue<State> q;
      unordered_set<string> visited;
      int nodesExpanded = 0;

      int blankPos = start.find('#');
      q.push(State(start, blankPos, 0, 0, 0));
      visited.insert(start);

      while (!q.empty())
      {
            State current = q.front();
            q.pop();
            nodesExpanded++;

            if (current.board == GOAL)
                  return {current.g, nodesExpanded};

            int row = current.blankPos / 4;
            int col = current.blankPos % 4;

            for (int i = 0; i < 4; i++)
            {
                  int newRow = row + dRow[i];
                  int newCol = col + dCol[i];

                  if (newRow >= 0 && newRow < 4 && newCol >= 0 && newCol < 4)
                  {
                        int newPos = newRow * 4 + newCol;
                        string newBoard = swapTiles(current.board, current.blankPos, newPos);

                        if (visited.find(newBoard) == visited.end())
                        {
                              q.push(State(newBoard, newPos, current.g + 1, nodesExpanded, 0));
                              visited.insert(newBoard);
                        }
                  }
            }
      }
      return {-1, -1};
}

// A* Algorithm (with heuristic choice)
pair<int, int> aStarSearch(string start, int heuristic)
{
      priority_queue<State, vector<State>, greater<State>> pq;
      unordered_set<string> visited;
      int nodesExpanded = 0;

      int blankPos = start.find('#');
      pq.push(State(start, blankPos, 0, 0, heuristic));
      visited.insert(start);

      while (!pq.empty())
      {
            State current = pq.top();
            pq.pop();
            nodesExpanded++;

            if (current.board == GOAL)
                  return {current.g, nodesExpanded};

            int row = current.blankPos / 4;
            int col = current.blankPos % 4;

            for (int i = 0; i < 4; i++)
            {
                  int newRow = row + dRow[i];
                  int newCol = col + dCol[i];

                  if (newRow >= 0 && newRow < 4 && newCol >= 0 && newCol < 4)
                  {
                        int newPos = newRow * 4 + newCol;
                        string newBoard = swapTiles(current.board, current.blankPos, newPos);

                        if (visited.find(newBoard) == visited.end())
                        {
                              pq.push(State(newBoard, newPos, current.g + 1, nodesExpanded, heuristic));
                              visited.insert(newBoard);
                        }
                  }
            }
      }
      return {-1, -1};
}

int main()
{
      // Precompute goal positions
      for (int i = 0; i < 16; i++)
      {
            goalRow[GOAL[i]] = i / 4;
            goalCol[GOAL[i]] = i % 4;
      }

      ifstream inputFile("puzzles.txt");
      ofstream outputFile("results.txt");

      outputFile << "Puzzle Solution BFS A*-h1 A*-h2\n";

      string puzzle;
      while (inputFile >> puzzle)
      {
            pair<int, int> bfsRes = bfs(puzzle);
            pair<int, int> aStarMisplaced = aStarSearch(puzzle, 1);
            pair<int, int> aStarManhattan = aStarSearch(puzzle, 2);

            outputFile << puzzle << " " << bfsRes.first << " " << bfsRes.second << " "
                       << aStarMisplaced.second << " " << aStarManhattan.second << "\n";
      }
      // Close the files.
      inputFile.close();
      outputFile.close();

      cout << "Results written to results.txt" << endl;
      return 0;
}
