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

fn make_string<T>(arr: &Vec<T>, sep: &str) -> String
    where T: std::string::ToString {
    let str_arr: Vec<String> = arr.iter().map(|x|x.to_string()).collect();
    str_arr.join(sep)
}
