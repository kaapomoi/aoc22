use std::fmt;
use std::fmt::Formatter;
use std::fs::File;
use std::io::{BufRead, BufReader};
use std::ops::Index;
use std::path::Path;

#[derive(Debug, Clone)]
struct HandError;

#[derive(Debug, Clone)]
struct OutcomeError;

enum Outcome {
    Win,
    Draw,
    Loss,
}

impl Outcome {
    fn new(c: char) -> Result<Outcome, OutcomeError> {
        match c {
            'X' => Ok(Outcome::Loss),
            'Y' => Ok(Outcome::Draw),
            'Z' => Ok(Outcome::Win),
            _ => Err(OutcomeError)
        }
    }
}

impl fmt::Display for OutcomeError{
    fn fmt(&self, f: &mut Formatter<'_>) -> fmt::Result {
        write!(f, "Invalid outcome input.")
    }
}

//
enum Hand {
    Rock,
    Paper,
    Scissors,
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

    fn check_opp_against_wanted_outcome(&self, wanted_outcome: Outcome) -> Hand {
        match wanted_outcome {
            Outcome::Win => {
                match self {
                    Hand::Rock => { Hand::Paper }
                    Hand::Paper => { Hand::Scissors }
                    Hand::Scissors => { Hand::Rock }
                }
            }
            Outcome::Draw => {
                match self {
                    Hand::Rock => { Hand::Rock }
                    Hand::Paper => { Hand::Paper }
                    Hand::Scissors => {Hand::Scissors }
                }
            }
            Outcome::Loss => {
                match self {
                    Hand::Rock => { Hand::Scissors }
                    Hand::Paper => { Hand::Rock }
                    Hand::Scissors => { Hand::Paper }
                }
            }
        }
    }
}

fn calculate_score(opponent: char, outcome: char) -> i32 {
    let mut score = 0;
    let wanted_outcome = Outcome::new(outcome).expect("Not a valid hand");
    let opp_hand = Hand::new(opponent).expect("Not a valid hand");

    match wanted_outcome {
        Outcome::Win => { score += 6; }
        Outcome::Draw => { score += 3; }
        Outcome::Loss => { score += 0; }
    }

    match opp_hand.check_opp_against_wanted_outcome(wanted_outcome) {
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
