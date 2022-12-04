use std::fs::File;
use std::io::{BufRead, BufReader};
use std::ops::Index;
use std::path::Path;

fn insert_current_into_top_three(top_three: &mut [i32; 3], current: i32) {
    let mut all_values = [top_three[0], top_three[1], current, top_three[2]];

    all_values.sort();
    all_values.reverse();

    *top_three = [all_values[0], all_values[1], all_values[2]];
}

fn main() {
    let mut top_three = [0; 3];

    let file = File::open(Path::new("input.txt")).expect("");
    let buffer = BufReader::new(file);
    let lines: Vec<String> = buffer.lines().map(|line| line.expect("Error parsing line")).collect();

    let mut current = 0;
    for line in lines {
        if line == "" {
            if top_three[2] < current {
                insert_current_into_top_three(&mut top_three, current);
            }
            current = 0;
        } else {
            let number = line.parse::<i32>().expect("Not a valid number");
            current += number;
        }
    }

    let mut total: i32 = top_three.iter().sum();

    println!("{}", total);
}
