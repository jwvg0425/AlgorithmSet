{-# LANGUAGE BangPatterns #-}
import Data.IntMap (IntMap)
import qualified Data.IntMap as IM

type Node = Int
type Adj b = IntMap b
type Context a b = (Adj b, a, Adj b)
type Graph a b = IntMap (Context a b)
type Decomp a b = (Context a b, Graph a b)

empty:: Graph a b
empty = IM.empty

null :: Graph a b -> Bool
null g = IM.null

gmap :: (Context a b -> Context c d) -> Graph a b -> Graph c d
gmap f g
  | null g = g
  | otherwise = f c & gmap f g'
  where (c, g') = matchAny g

ufold :: (Context a b -> c -> c) ->  c -> Graph a b -> c
ufold f u g
  | null g = u
  | otherwise = f c (ufold f u g')
  where (c, g') = matchAny g

