#include <iostream>
#include <string>

using namespace std;

void findAvailableMoves(const string &board)
{
      int blankPos = board.find('#');
      int row = blankPos / 4;
      int col = blankPos % 4;

      if (row > 0)
            cout << "UP" << endl;
      if (row < 3)
            cout << "DOWN" << endl;
      if (col > 0)
            cout << "LEFT" << endl;
      if (col < 3)
            cout << "RIGHT" << endl;
}

int main()
{
      string board;
      cin >> board;
      findAvailableMoves(board);
      return 0;
}
