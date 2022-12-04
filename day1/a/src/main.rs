use std::fs::File;
use std::io::{BufRead, BufReader};
use std::path::Path;

fn main() {
    let mut largest = 0;

    let file = File::open(Path::new("input.txt")).expect("");
    let buffer = BufReader::new(file);
    let lines: Vec<String> = buffer.lines().map(|line| line.expect("Error parsing line")).collect();

    let mut current = 0;
    for line in lines {
        if line == "" {
            if largest < current {
                largest = current;
            }
            current = 0;
        } else {
            let number = line.parse::<i32>().expect("Not a valid number");
            current += number;
        }
    }

    println!("{}", largest);
}
