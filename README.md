# SettlersOfCatanAI
Opening Strategies of Settlers of Catan using OpenGL


There are always 19 Regions:
->We will simplify our game by always having the barren region in the middle
->Always starting the number system in the top most, left most region, and moving in a clockwise decreasing spriral
->Regions will be identified by a letter from A to R (where the barren region is labeled as X)
->Regions lettered A through R will always have the same probability value (a number between 2 and 12)
  ->Prob(2) = Probability of rolling two dice that sum to 2            (i.e. two 1's)
->Every Region (A thought R, and X) will have 6 corners, and 6 sides, numbered from the top left point moving clockwise
->Trading ports will always be the same
