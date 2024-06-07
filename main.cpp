#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

// Basic encryption function for demonstration
string encrypt(string text, int key) {
    for (char &c : text) {
        c += key;
    }
    return text;
}

// Basic decryption function for demonstration
string decrypt(string text, int key) {
    for (char &c : text) {
        c -= key;
    }
    return text;
}

// Voter class
class Voter {
public:
    string name;
    string encrypted_vote;

    Voter(string name, string vote) {
        this->name = name;
        this->encrypted_vote = encrypt(vote, 3); // Encrypting vote with a simple key
    }

    void displayVote() {
        std::cout << "Name: " << name << ", Vote: " << decrypt(encrypted_vote, 3) << endl;
    }
};

// Voting System class
class VotingSystem {
private:
    vector<Voter> voters;
    map<string, int> voteCount;

public:
    void addVoter(string name, string vote) {
        Voter voter(name, vote);
        voters.push_back(voter);
        voteCount[vote]++;
    }

    void displayResults() {
        cout << "Voting Results:" << endl;
        for (const auto &pair : voteCount) {
            cout << pair.first << ": " << pair.second << " votes" << endl;
        }
    }

    void saveVotes() {
        ofstream file("votes.txt");
        for (const Voter &voter : voters) {
            file << voter.name << "," << voter.encrypted_vote << endl;
        }
        file.close();
    }

    void loadVotes() {
        ifstream file("votes.txt");
        string line;
        while (getline(file, line)) {
            size_t pos = line.find(",");
            string name = line.substr(0, pos);
            string encrypted_vote = line.substr(pos + 1);
            voters.emplace_back(name, encrypted_vote);
            voteCount[decrypt(encrypted_vote, 3)]++;
        }
        file.close();
    }
};

int main() {
    VotingSystem vs;

    vs.addVoter("Alice", "Candidate1");
    vs.addVoter("Bob", "Candidate2");
    vs.addVoter("Charlie", "Candidate1");

    vs.saveVotes();

    vs.displayResults();

    // Loading votes from file and displaying results again to demonstrate persistence
    VotingSystem vs2;
    vs2.loadVotes();
    vs2.displayResults();

    return 0;
}
