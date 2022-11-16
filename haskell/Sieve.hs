sieve :: Int -> UArray Int Bool
sieve n = runSTUArray $ do
  sieve <- newArray (2, n) True
  forM_ [2..n] $ \p -> do
    isPrime <- readArray sieve p
    when isPrime $ do
      forM_ [p*2, p*3 .. n] $ \k -> do
        writeArray sieve k False
  return sieve

primesUpto :: Int -> [Int]
primesUpto n = [p | (p, True) <- assocs $ sieve n]