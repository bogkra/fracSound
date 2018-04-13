#include <gtest/gtest.h>
#include "bowling.hpp"

using namespace std;

class bowlingTest : public ::testing::Test
{
public:
// examples:
 const string perfectScore = "X|X|X|X|X|X|X|X|X|X||XX";
 const string alwaysAlmostPerfect = "9-|9-|9-|9-|9-|9-|9-|9-|9-|9-||";
 const string twentyOneFives = "5/|5/|5/|5/|5/|5/|5/|5/|5/|5/||5";
 const string mixed = "X|7/|9-|X|-8|8/|-6|X|X|X||81";
 const string perfectNoob = "--|--|--|--|--|--|--|--|--|--||";
};


// tests of fillFrames method:

TEST_F(bowlingTest, emptyFrame)
{
  Bowling game("");  
  auto frames = game.getFrames();
  ASSERT_FALSE(frames.empty());
  ASSERT_EQ(frames.at(0), "");
}


TEST_F(bowlingTest, oneSimpleFrame)
{
  string s = "a";
  Bowling game(s);  
  auto frames = game.getFrames();
  ASSERT_FALSE(frames.empty());
  ASSERT_EQ(frames.at(0), s);
}


TEST_F(bowlingTest, twoEmptyFrames)
{
  Bowling game("|");  
  auto frames = game.getFrames();
  ASSERT_FALSE(frames.empty());
  ASSERT_EQ(frames.at(0), "");
  ASSERT_EQ(frames.at(1), "");
}

TEST_F(bowlingTest, threeFrames)
{
  Bowling game("||");  
  auto frames = game.getFrames();
  ASSERT_EQ(frames.at(0), "");
  ASSERT_EQ(frames.at(1), "");
  ASSERT_EQ(frames.at(2), "");
}

TEST_F(bowlingTest, mixedFrames)
{
  Bowling game(mixed);  
  const Frames expected = {"X","7/","9-","X","-8","8/","-6","X","X","X","81"};
  ASSERT_EQ(game.getFrames(), expected);
}

TEST_F(bowlingTest, xsFrames)
{
  Bowling game(perfectScore);  
  const Frames expected = {"X","X","X","X","X","X","X","X","X","X","XX"};
  ASSERT_EQ(game.getFrames(), expected);
}

TEST_F(bowlingTest, _9minusFrames)
{
  Bowling game(alwaysAlmostPerfect);  
  const Frames expected = {"9-","9-","9-","9-","9-","9-","9-","9-","9-","9-",""};
  ASSERT_EQ(game.getFrames(), expected);}

TEST_F(bowlingTest, _5slashFrames)
{
  Bowling game(twentyOneFives);  
  const Frames expected = {"5/","5/","5/","5/","5/","5/","5/","5/","5/","5/","5"};
  ASSERT_EQ(game.getFrames(), expected);
}

// tests of validateFrames method:

TEST_F(bowlingTest, validationTooManySymbols)
{
    Bowling game("XXX|7/|9-|X|-8|8/|-6|X|X|X||81");
    ASSERT_FALSE(game.validateFrames());
}

TEST_F(bowlingTest, validationTooManyDigits)
{
    Bowling game1("99|X|X|X|X|X|X|X|X|X||XX");
    ASSERT_FALSE(game1.validateFrames());
}


TEST_F(bowlingTest, validationIncorrectSeparators)
{
    Bowling game1("X|X|X|X|X|X||X|X|X|X|XX");
    ASSERT_FALSE(game1.validateFrames());
}

TEST_F(bowlingTest, validationIncorrectSymbol)
{
    Bowling game2("Y|7/|9-|X|-8|8/|-6|X|X|X||81");
    ASSERT_FALSE(game2.validateFrames());

    Bowling game3(mixed);
    ASSERT_TRUE(game3.validateFrames());
}

TEST_F(bowlingTest, validationTooFewSymbols)
{
    Bowling game1("|||X||81");
    ASSERT_FALSE(game1.validateFrames());

    Bowling game2("X|7/|9-|X|||-8|8/|-6|X|X|X||81");
    ASSERT_FALSE(game2.validateFrames());

    Bowling game3("X|7/|9-|X|||||-8|8/|-6|X|X|X||81");
    ASSERT_FALSE(game3.validateFrames());
}


// test of extras:

TEST_F(bowlingTest, noExtras)
{
  Bowling game(perfectNoob);
  ASSERT_EQ(game.countExtras(), 0);
}

TEST_F(bowlingTest, extrasforFives)
{
  Bowling game(twentyOneFives);
  ASSERT_EQ(game.countExtras(), 50);
}

TEST_F(bowlingTest, doesExtraSum)
{
  Bowling game("X|34|--|--|--|--|--|--|--|--||");
  ASSERT_EQ(game.countExtras(), 7);
}


TEST_F(bowlingTest, doesExtraCountSpare)
{
  Bowling game("X|3/|--|--|--|--|--|--|--|--||");
  ASSERT_EQ(game.countExtras(), 10);
}

TEST_F(bowlingTest, twoStrikesExtra)
{

  Bowling game("X|X|23|--|--|--|--|--|--|--||");
  ASSERT_EQ(game.countExtras(), 17);
}

TEST_F(bowlingTest, perfectExtra)
{
  Bowling game(perfectScore);
  ASSERT_EQ(game.countExtras(), 200);
}



// test of total score:

TEST_F(bowlingTest, countScore)
{
    Bowling game1(perfectScore);
    ASSERT_EQ(game1.countScore(),300);

    Bowling game2(alwaysAlmostPerfect);
    ASSERT_EQ(game2.countScore(), 90);

    Bowling game3(twentyOneFives);
    ASSERT_EQ(game3.countScore(),150);

    Bowling game4(mixed);
    ASSERT_EQ(game4.countScore(),167);

    Bowling game5("X|3/|--|--|--|--|--|--|--|--||");
    ASSERT_EQ(game5.countScore(),10+10 + 10);

    Bowling game6("X|X|23|--|--|--|--|--|--|--||");
    ASSERT_EQ(game6.countScore(),10+10+5 + 12 + 5);

    Bowling game7("X|34|--|--|--|--|--|--|--|--||");
    ASSERT_EQ(game7.countScore(),10+7 + 7);

    Bowling game8("--|--|--|1-|--|--|--|--|--|--||");
    ASSERT_EQ(game8.countScore(),1);

    Bowling game9("--|--|--|--|--|--|2-|--|--|--||");
    ASSERT_EQ(game9.countScore(), 2);

    Bowling game10("--|X|--|--|--|--|--|--|--|--||");
    ASSERT_EQ(game10.countScore(), 10);

    Bowling game11("--|--|--|--|--|--|--|8/|--|--||");
    ASSERT_EQ(game11.countScore(), 10);
}

TEST_F(bowlingTest, incorrectData)
{
  Bowling game1("111|--|--|--|--|--|--|--|--|--||");
  ASSERT_THROW(game1.countScore(), std::invalid_argument);

  Bowling game2("0-|--|--|--|--|--|--|--|--|--||");
  ASSERT_THROW(game2.countScore(), std::invalid_argument);
}

