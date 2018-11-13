/*----------------------------------------------------------
 *				HTBLA-Leonding / Klasse: 2AHDV
 * ---------------------------------------------------------
 * Exercise Number: 0
 * Title:			chess.c
 * Author:			P. Bauer
 * Due Date:		November 03, 2010
 * ----------------------------------------------------------
 * Description:
 * Implementation of basic chess functions.
 * ----------------------------------------------------------
 */
 #include <stdlib.h>
 #include "general.h"
 #include "chess.h"

 bool is_move_from_base_line (enum PieceColor color, Rank rank)
 {
   if (color == White && rank == 2) {
     return true;
   }
   else if (color == Black && rank == 2) {
     return true;
   }
   return false;
 }

 bool is_square_ok (File file, Rank rank)
 {
   return (file <= 'h') && (file >= 'a') && (rank <= 8) && (rank > 0);
 }

 bool is_piece (struct ChessPiece pc, enum PieceColor color, enum PieceType type)
 {
   return pc.color == color && pc.type == type;
 }
 void init_chess_board (ChessBoard chess_board)
 {
   for (int x = 0; x < 8; x++) {
     for (int y = 0; y < 8; y++) {
       chess_board[x][y].is_occupied = false;
     }
   }
 }
 struct ChessSquare * get_square (ChessBoard chess_board, File file, Rank rank)
 {
   if(is_square_ok(file, rank))
   {
     return &chess_board[rank - 1][file - 'a'];
   }
   else
   {
    return 0;
   }
 }
 bool is_square_occupied (ChessBoard chess_board, File file, Rank rank)
 {
   return chess_board[rank - 1][file - 'a'].is_occupied;
 }
 bool add_piece (ChessBoard chess_board, File file, Rank rank, struct ChessPiece piece)
 {
   if(!is_square_ok(file, rank) || chess_board[rank - 1][file - 'a'].is_occupied == true)
   {
     return false;
   }
   chess_board[rank - 1][file-'a'].is_occupied = true;
   chess_board[rank - 1][file-'a'].piece = piece;
   return true;
 }
 struct ChessPiece 	get_piece (ChessBoard chess_board, File file, Rank rank)
 {
   struct ChessPiece piece_return;
   piece_return.type = NoPiece;

   if(!is_square_ok(file, rank) || chess_board[rank -1][file - 'a'].is_occupied == false)
   {
     return piece_return;
   }
   return chess_board[rank - 1][file - 'a'].piece;
 }
 void setup_chess_board (ChessBoard chess_board)
 {
   init_chess_board(chess_board);
   static struct ChessPiece white_pawn = {White, Pawn};
   static struct ChessPiece white_bishop = {White, Bishop};
   static struct ChessPiece white_king = {White, King};
   static struct ChessPiece white_queen = {White, Queen};
   static struct ChessPiece white_knight = {White, Knight};
   static struct ChessPiece white_rook = {White, Rook};

   static struct ChessPiece black_pawn = {Black, Pawn};
   static struct ChessPiece black_rook = {Black, Rook};
   static struct ChessPiece black_knight = {Black, Knight};
   static struct ChessPiece black_bishop = {Black, Bishop};
   static struct ChessPiece black_queen = {Black, Queen};
   static struct ChessPiece black_king = {Black, King};

   add_piece(chess_board, 'a', 1 , white_rook);
   add_piece(chess_board, 'b', 1 , white_knight);
   add_piece(chess_board, 'c', 1 , white_bishop);
   add_piece(chess_board, 'd', 1 , white_queen);
   add_piece(chess_board, 'e', 1 , white_king);
   add_piece(chess_board, 'f', 1 , white_bishop);
   add_piece(chess_board, 'g', 1 , white_knight);
   add_piece(chess_board, 'h', 1 , white_rook);

   for(int i = 'a'; i <= 'h'; i++)
   {
     add_piece(chess_board, i, 2, white_pawn);
     add_piece(chess_board, i, 7, black_pawn);
   }

   add_piece(chess_board, 'a', 8 , black_rook);
   add_piece(chess_board, 'b', 8 , black_knight);
   add_piece(chess_board, 'c', 8 , black_bishop);
   add_piece(chess_board, 'd', 8 , black_queen);
   add_piece(chess_board, 'e', 8 , black_king);
   add_piece(chess_board, 'f', 8 , black_bishop);
   add_piece(chess_board, 'g', 8 , black_knight);
   add_piece(chess_board, 'h', 8 , black_rook);
 }


 bool remove_piece (ChessBoard chess_board, File file, Rank rank)
 {
   if (is_square_occupied(chess_board, file, rank) && is_square_ok(file, rank)) {
     chess_board[rank - 1][file - 'a'].is_occupied = false;
     chess_board[rank -1][file - 'a'].piece.type = NoPiece;
     return true;
   }
   return false;
 }
 bool squares_share_file (File s1_f, Rank s1_r, File s2_f, Rank s2_r)
 {
   return s1_f==s2_f && is_square_ok(s1_f,s1_r) && is_square_ok(s2_f,s2_r);
 }
 bool squares_share_rank (File s1_f, Rank s1_r, File s2_f, Rank s2_r)
 {
   return s1_r==s2_r && is_square_ok(s1_f,s1_r) && is_square_ok(s2_f,s2_r);
 }
 bool squares_share_diagonal (File s1_f, Rank s1_r, File s2_f, Rank s2_r)
 {
   int file_sum;
   int rank_sum;

   file_sum = s1_f - s2_f;

   if(file_sum<0)
   {
     file_sum=file_sum-file_sum-file_sum;
   }

   rank_sum=s1_r-s2_r;

   if(rank_sum<0)
   {
     rank_sum=rank_sum-rank_sum-rank_sum;
   }
   return rank_sum == file_sum && is_square_ok(s1_f,s1_r) && is_square_ok(s2_f,s2_r);
 }

 bool squares_share_knights_move (File s1_f, Rank s1_r, File s2_f, Rank s2_r)
 {
   int file_sum;
   int rank_sum;
   file_sum = s1_f - s2_f;

   if(file_sum<0)
   {
     file_sum=file_sum-file_sum-file_sum;
   }

   rank_sum=s1_r-s2_r;

   if(rank_sum<0)
   {
     rank_sum=rank_sum-rank_sum-rank_sum;
   }

   return is_square_ok(s1_f,s1_r) && is_square_ok(s2_f,s2_r) && file_sum + rank_sum == 3 && !squares_share_file(s1_f, s1_r, s2_f, s2_r);
 }

 bool squares_share_pawns_move (enum PieceColor color, enum MoveType move, File s1_f, Rank s1_r, File s2_f, Rank s2_r)
 {
   if(move==NormalMove && color==White && s1_f==s2_f && s1_r+2 == s2_r && s1_r==2)
    {
          return true;
    }
    else if(move==NormalMove && color==White && s1_f==s2_f && s1_r+1 == s2_r && s1_r>1)
    {
      return true;
    }
    else if(move==CaptureMove && color==White && (s1_f==s2_f+1 || s1_f==s2_f-1) && s1_r+1 == s2_r)
    {
      return true;
    }

    else if(move==NormalMove && color==Black && s1_f==s2_f && s1_r-2 == s2_r && s1_r==7)
    {
      return true;
    }
    else if(move==NormalMove && color==Black && s1_f==s2_f && s1_r-1 == s2_r && s1_r<8)
    {
      return true;
    }

    else if(move==CaptureMove && color==Black && (s1_f==s2_f+1 || s1_f==s2_f-1) && s1_r-1 == s2_r)
    {
      return true;
    }

    return false;
 }
 bool squares_share_queens_move (File s1_f, Rank s1_r, File s2_f, Rank s2_r)
 {
   return squares_share_rank(s1_f, s1_r, s2_f, s2_r) || squares_share_file (s1_f, s1_r, s2_f, s2_r) || squares_share_diagonal(s1_f, s1_r, s2_f, s2_r);
 }

 bool squares_share_kings_move (File s1_f, Rank s1_r, File s2_f, Rank s2_r)
 {
   int x;
   int y;

   x = s1_r - s2_r;
   y = s1_f - s2_f;

   return x <= 1 && x >= -1 && y <= 1 && y >= -1 && (x != 0 || y != 0);
 }
