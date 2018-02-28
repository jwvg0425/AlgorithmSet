{-# LANGUAGE BangPatterns #-}
import Data.List
import Data.Maybe
import Data.Function (fix)
import Data.Array (Array, array, (!))
import qualified Data.ByteString as BS
import qualified Data.ByteString.Char8 as BS8
 
getInts :: IO [Int]
getInts = (map parseInt . BS8.words) <$> BS.getLine 
    where parseInt = fst . fromJust . BS8.readInt

data Tree a = Tree (Tree a) a (Tree a)

instance Functor Tree where
    fmap f (Tree l m r) = Tree (fmap f l) (f m) (fmap f r)

index :: Tree a -> Int -> a
index (Tree _ m _) 0 = m
index (Tree l _ r) n = case (n - 1) `divMod` 2 of
    (q,0) -> index l q
    (q,1) -> index r q

nats :: Tree Int
nats = go 0 1
    where go !n !s = Tree (go l s') n (go r s')
            where l = n + s
                  r = l + s
                  s' = s * 2

memo :: (Int -> a) -> (Int -> a)
memo f = index cached
    where cached = fmap f nats

memo2 :: (Int -> Int -> a) -> (Int -> Int -> a)
memo2 f = memo (\x -> memo (f x))

memo3 :: (Int -> Int -> Int -> a) -> (Int -> Int -> Int -> a)
memo3 f = memo (\x -> memo2 (f x))

{- dp example
fibo 0 = 0
fibo 1 = 1
fibo n = mfibo (n-1) + mfibo (n-2)

mfibo = memo f
-}