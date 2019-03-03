use std::io;

fn read_list<T>() -> Vec<T>
    where T: std::str::FromStr,
          <T as std::str::FromStr>::Err: std::fmt::Debug {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    input.as_mut_str().split_whitespace().map(|word| word.parse().unwrap()).collect()
}

fn read_string() -> Vec<char> {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    input.chars().collect()
}
