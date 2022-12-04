use std::fmt;
use std::fmt::Formatter;
use std::fs::File;
use std::io::{BufRead, BufReader};
use std::ops::Index;
use std::path::Path;

#[derive(Debug, Clone)]
struct HandError;

enum Hand {
    Rock,
    Paper,
    Scissors,
}

enum Outcome {
    Win,
    Draw,
    Loss,
}

impl fmt::Display for HandError {
    fn fmt(&self, f: &mut Formatter<'_>) -> fmt::Result {
        write!(f, "Invalid hand.")
    }
}

impl Hand {
    fn new(c: char) -> Result<Hand, HandError> {
        match c {
            'A' | 'X' => Ok(Hand::Rock),
            'B' | 'Y' => Ok(Hand::Paper),
            'C' | 'Z' => Ok(Hand::Scissors),
            _ => Err(HandError)
        }
    }

    fn check_against_other(&self, other: Hand) -> Outcome {
        match self {
            Hand::Rock => {
                match other {
                    Hand::Rock => { Outcome::Draw }
                    Hand::Paper => { Outcome::Loss }
                    Hand::Scissors => { Outcome::Win }
                }
            }
            Hand::Paper => {
                match other {
                    Hand::Rock => { Outcome::Win }
                    Hand::Paper => { Outcome::Draw }
                    Hand::Scissors => { Outcome::Loss }
                }
            }
            Hand::Scissors => {
                match other {
                    Hand::Rock => { Outcome::Loss }
                    Hand::Paper => { Outcome::Win }
                    Hand::Scissors => { Outcome::Draw }
                }
            }
        }
    }
}

fn calculate_score(opponent: char, me: char) -> i32 {
    let mut score = 0;
    let my_hand = Hand::new(me).expect("Not a valid hand");
    let opp_hand = Hand::new(opponent).expect("Not a valid hand");

    match my_hand.check_against_other(opp_hand) {
        Outcome::Win => { score += 6; }
        Outcome::Draw => { score += 3; }
        Outcome::Loss => { score += 0; }
    }

    match my_hand {
        Hand::Rock => { score += 1; }
        Hand::Paper => { score += 2; }
        Hand::Scissors => { score += 3; }
    }

    score
}

fn main() {
    let file = File::open(Path::new("input.txt")).expect("");
    let buffer = BufReader::new(file);
    let lines: Vec<String> = buffer.lines().map(|line| line.expect("Error parsing line")).collect();

    let mut score_total: i32 = 0;
    for line in lines {
        println!("{}", line);
        score_total += calculate_score(line.chars().nth(0).unwrap(), line.chars().nth(2).unwrap());
    }

    println!("{}", score_total);
}
