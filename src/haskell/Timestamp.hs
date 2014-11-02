module Timestamp where

import Data.List
import Data.List.Split
import System.Environment
import System.IO

hourToMinute :: Int -> Int
hourToMinute x = x * 60

dayToHour :: Int -> Int
dayToHour d = d * 24

paysections :: Int -> Int
paysections m = fst $ divMod m 15

timestampToMinutes' :: String -> Int
timestampToMinutes' t = (hourToMinute (((map (\x -> read x::Int) (splitOn ":" t))) !! 0)) + ((map (\x -> read x::Int) (splitOn ":" t)) !! 1)

timestampToMinutes :: String -> Int
timestampToMinutes t = (hourToMinute (timetriple !! 0)) + (timetriple !! 1)
    where timetriple = map (\x -> read x::Int) (splitOn ":" t)

getDates :: [String] -> [String]
getDates x = map (head . splitOn "\t" . init) x

getTimestamps :: [String] -> [String]
getTimestamps x = map (last . splitOn "\t" . init) x

isSameDay :: String -> (String,String) -> Bool
isSameDay d (a,_) = 
    if (a == d)
        then True
        else False

main :: IO ()
main = do
    contents <- readFile "test2.dat"
    let dates = getDates (lines contents)
    let timestamps = getTimestamps (lines contents)
    let records = zip dates timestamps
    let numDays = length $ nub dates
    putStrLn ("Number of Days: " ++ (show numDays))
    putStrLn ("Number of 15 Minute Intervals: " ++ (show $ foldr (+) 0 $ map (length . nub . (map (paysections . timestampToMinutes . snd))) $ map (\x -> filter (isSameDay x) records) (nub dates)))
