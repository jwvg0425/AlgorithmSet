import qualified Data.Sequence as S

data DSet = DSet (S.Seq Int)

a !. b = fromJust $ a S.!? b

merge :: Int -> Int -> DSet -> DSet
merge a b (DSet sq) = if ra == rb then DSet sq'' else DSet (S.update rb ra sq'')
    where (ra, DSet sq') = root a (DSet sq)
          (rb, DSet sq'') = root b (DSet sq')

root :: Int -> DSet -> (Int, DSet)
root a (DSet sq) = let r = f a in (r, DSet (S.update a r sq))
    where f i = if i == sq !. i then i else f (sq !. i)