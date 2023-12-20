//
// Created by robert12 on 10/16/23.
//

#ifndef CHESS_2_0_PIECE_H
#define CHESS_2_0_PIECE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <string>
#include <utility>
#include <vector>
#include "Box.h"
#include <list>

using std::pair;
using std::list;
using std::vector;
class Piece : public QGraphicsPixmapItem {
protected:
    Box *pieceBox;
    bool movable;
    int pieceX, pieceY;
    std::string pieceTeam;
    std::string imagePath;
    vector<vector<Box*>>chessBoard;
    list<pair<int, int>> movable_pos;
    list<pair<int, int>> opponents_pos;
public:
    Piece( std::string &imagePath_, std::string& pieceTeam_, vector<vector<Box*>>& chessBoard_, Box *pieceBox_, int X, int Y,
          bool movable_);

    /**
 * Get the team to which the piece belongs.
 * @return std::string 'Team' (black/white)
 */
    virtual std::string getPieceTeam();

/**
 * Get the path of the image that is behind the piece.
 */
    virtual std::string getImagePath();

/**
 * Find movable positions for "this" piece.
 * @return std::list<std::pair<int,int>> Movable positions.
 */
    virtual std::list<std::pair<int, int>> &getMovablePos();

/**
 * Find the positions of the opponents that can be taken by "this" piece.
 * @return std::list<std::pair<int,int>> Positions of opponents.
 */
    virtual std::list<std::pair<int, int>> &getOpponentsPos();

/**
 * Intersect the lists of movable positions and opponents' positions.
 * @return std::list<std::pair<int, int>> Intersection of lists.
 */
    virtual std::list<std::pair<int, int>>& intersectLists();

/**
 * Get the x-coordinate of the piece.
 * @return int x-coordinate.
 */
    virtual int getPieceX();

/**
 * Get the y-coordinate of the piece.
 * @return int y-coordinate.
 */
    virtual int getPieceY();

/**
 * Set the team to which the piece belongs.
 * @param newPieceTeam New team value (black/white).
 */
    virtual void setPieceTeam(std::string newPieceTeam);

/**
 * Set the path of the image that is behind the piece.
 * @param newImagePath New image path.
 */
    virtual void setImagePath(std::string newImagePath);

/**
 * Set the movable positions for "this" piece.
 * @param new_movable_pos New list of movable positions.
 */
    virtual void setMovablePos(std::list<std::pair<int, int>> &new_movable_pos);

/**
 * Set the parent box of the piece.
 * @param parentBox Pointer to the parent box.
 */
    virtual void setParentBox(Box *parentBox);

/**
 * Set the position of the piece.
 */
    virtual void setPosition();

/**
 * Set the coordinates of the piece.
 * @param X x-coordinate.
 * @param Y y-coordinate.
 */
    virtual void setCoordonates(int X, int Y);

/**
 * Unblock the piece.
 */
    virtual void unblockPiece();

/**
 * Block the piece.
 */
    virtual void blockPiece();

/**
 * Check if the piece is movable.
 * @return bool True if movable, false otherwise.
 */
    virtual bool isMovable();

/**
 * Add opponent coordinates to the piece's data.
 * @param _op_coords Opponent coordinates to add.
 */
    virtual void AddOpCoords(std::pair<int, int> _op_coords);

/**
 * Add movable positions to the piece's data.
 * @param _op_coords Movable positions to add.
 */
    virtual void AddMovablePos(std::pair<int, int> _op_coords);

/**
 * Delete opponent coordinates from the piece's data.
 */
    virtual void DeleteOpCoords();

/**
 * Delete movable positions from the piece's data.
 */
    virtual void DeleteMovablePos();

/**
 * Check if the specified coordinates are of an opponent piece.
 * @param X x-coordinate.
 * @param Y y-coordinate.
 * @return bool True if opponent, false otherwise.
 */
    virtual bool isOpponent(int X, int Y);

/**
 * Check if the specified coordinates are inside the board.
 * @param X x-coordinate.
 * @param Y y-coordinate.
 * @return bool True if inside, false otherwise.
 */
    virtual bool inside(int X, int Y);

/**
 * Check if the specified coordinates are valid for the piece's movement.
 * @param X x-coordinate.
 * @param Y y-coordinate.
 * @return bool True if valid, false otherwise.
 */
    virtual bool validPos(int X, int Y);

/**
 * Perform the moves based on the specified coordinates.
 * @param X x-coordinate.
 * @param Y y-coordinate.
 */
    virtual void Moves(int X, int Y) = 0;

/**
 * Color the path of the piece.
 */
    virtual void colorPath();

/**
 * Check for other pieces along a specified direction.
 * @param startX Starting x-coordinate.
 * @param stopX Stopping x-coordinate (modified if needed).
 * @param startY Starting y-coordinate.
 * @param stopY Stopping y-coordinate (modified if needed).
 * @param incrementX Increment for x-coordinate.
 * @param incrementY Increment for y-coordinate.
 * @return int Number of pieces found along the specified direction.
 */
    int CheckForOthers(int startX, int& stopX, int startY, int& stopY, int incrementX, int incrementY);

/**
 * Check the state of the piece.
 * @return int The state of the piece.
 */
    virtual int Check() = 0;


};


#endif //CHESS_2_0_PIECE_H
