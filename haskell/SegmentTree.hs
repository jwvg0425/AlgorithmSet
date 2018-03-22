import qualified Data.Sequence as S

data SegTree x = Node { val :: x, segment :: (Int, Int), merge :: (x->x->x), left :: SegTree x, right :: SegTree x } | Empty

isEmpty :: SegTree x -> Bool
isEmpty Empty = True
isEmpty _ = False

query :: SegTree x -> Int -> Int -> x
query (Node v (l,r) merge lc rc) ls rs
    | l == ls && r == rs = v
    | not (isEmpty lc) && ls >= (fst $ segment rc) = query rc ls rs
    | not (isEmpty rc) && rs <= (snd $ segment lc) = query lc ls rs
    | otherwise = let lval = query lc ls (snd $ segment lc)
                      rval = query rc (fst $ segment rc) rs
                  in merge lval rval

update :: SegTree x -> Int -> x -> SegTree x
update (Node v (l,r) merge lc rc) idx nv
    | l == idx && r == idx = Node nv (l,r) merge lc rc 
    | otherwise = (Node (merge (val lc') (val rc')) (l,r) merge lc' rc')
    where rc' = if not (isEmpty lc) && idx >= (fst $ segment rc) then update rc idx nv else rc
          lc' = if not (isEmpty rc) && idx <= (snd $ segment lc) then update lc idx nv else lc

makeSegTree :: S.Seq x -> (x -> x -> x) -> Int -> Int -> SegTree x
makeSegTree xs merge l r
    | S.null xs = Empty
    | S.length xs == 1 = Node (xs `S.index` 0) (l,r) merge Empty Empty
    | otherwise = Node pval (l, r) merge leftSegTree rightSegTree
    where len = (S.length xs + 1) `div` 2
          (xl, xr) = S.splitAt len xs
          leftSegTree = makeSegTree xl merge l (l+len-1)
          rightSegTree = makeSegTree xr merge (l+len) r
          pval = if isEmpty leftSegTree then val rightSegTree 
                 else if isEmpty rightSegTree then val leftSegTree
                 else merge (val leftSegTree) (val rightSegTree)

segFromList :: (x -> x -> x) -> [x] -> SegTree x
segFromList merge xs = makeSegTree (S.fromList xs) merge 0 (length xs - 1)