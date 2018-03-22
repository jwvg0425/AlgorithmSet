import qualified Data.Sequence as S
import qualified Data.ByteString as BS
import qualified Data.ByteString.Char8 as BS8

construct ::BS.ByteString -> S.Seq Int
construct str
    | BS.null str = S.empty
    | isSpace (BS8.head str) = construct (BS8.tail str)
    | otherwise = let Just (i, other) = BS8.readInt str in i S.<| construct other

getIntSeq :: IO (S.Seq Int)
getIntSeq = construct <$> BS.getLine