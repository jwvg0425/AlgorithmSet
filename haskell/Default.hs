{-# LANGUAGE BangPatterns #-}
import System.IO
import Control.Applicative
import Control.Monad
import Data.Char
import Data.List
import Data.Maybe
import Data.Monoid
import Data.Function (fix)
import Data.Array (Array, array, (!))
import Data.ByteString.Lazy.Builder
import Data.ByteString.Lazy.Builder.ASCII
import qualified Data.Map as Map
import qualified Data.ByteString as BS
import qualified Data.ByteString.Char8 as BS8

construct :: (BS.ByteString -> Maybe (a, BS.ByteString)) -> BS.ByteString -> [a]
construct reader str
    | BS.null str = []
    | isSpace (BS8.head str) = construct reader (BS8.tail str)
    | otherwise = let Just (i, other) = reader str in i : construct reader other

getInts :: IO [Int]
getInts = construct BS8.readInt <$> BS.getLine

getIntegers :: IO [Integer]
getIntegers = construct BS8.readInteger <$> BS.getLine

printInts :: [Int] -> IO ()
printInts = putStrLn . intercalate " " . map show

(!) = (Map.!)

main = input >>= output . solve

input =
output =
solve =
