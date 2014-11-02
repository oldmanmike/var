-------------------------------------------------------------
-- Program: A Simple Base Converter
-- Author: Michael Carpenter
-- Date: 11/2/13
-- Note:  This is obviously not C/C++. 
--        I designed my program in Haskell before learning 
--        that there was a language restriction.I used Haskell 
--        because I found it more intuitive and the solution 
--        seemed more natural and correct. 
--        I can convert this into C/C++, 
--        but I don't know if I'll have it done in time.
---------------------------------------------------------------

toList :: Integral x => x -> [x]
toList 0  = []
toList x  = toList (x `div` 10) ++ [x `mod` 10]

baseMult :: Int -> [Int] -> [Int] -> [Int]
baseMult base _ _           | base < 1              = error "Base is too small"
baseMult _ [] _                                     = []
baseMult _ (x:xs) []                                = error "Oh dear, how did you manage to do that?"
baseMult base (x:xs) (y:ys)                         = (x * base^y):baseMult base xs ys

dec2Base :: Int -> Int -> [Int]
dec2Base base _             | base < 1  = error "Base is too small"
dec2Base _ n                | n <= 0    = []
dec2Base base num                       = (mod num base):dec2Base base (div num base) 

baseConvert :: Int -> Int -> Int -> [Int]
baseConvert base1 _ _       | base1 < 1 = error "First base is too small"
baseConvert _ base2 _       | base2 < 1 = error "Second base is too small"
baseConvert _ _ n           | n <= 0    = error "Number is too small"
baseConvert base1 base2 num = reverse 
                              (dec2Base base2 
                              (sum
                              (baseMult base1 
                              (toList num)                              
                              (reverse [0 .. ((length (toList num)) - 1)]))))
