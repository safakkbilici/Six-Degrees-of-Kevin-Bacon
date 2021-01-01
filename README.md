# Six Degrees of Kevin Bacon
Six Degrees of Kevin Bacon or "Bacon's Law" is a parlour game based on the "six degrees of separation" concept, which posits that any two people on Earth are six or fewer acquaintance links apart. Movie buffs challenge each other to find the shortest path between an arbitrary actor and prolific actor Kevin Bacon. It rests on the assumption that anyone involved in the Hollywood film industry can be linked through their film roles to Bacon within six steps. In 2007, Bacon started a charitable organization called SixDegrees.org. In 2020, Bacon started a podcast called The Last Degree of Kevin Bacon.
## Bacon Number
The Bacon number of an actor is the number of degrees of separation he or she has from Bacon, as defined by the game. This is an application of the Erdős number concept to the Hollywood movie industry. The higher the Bacon number, the greater the separation from Kevin Bacon the actor is.

The computation of a Bacon number for actor X is a "shortest path" algorithm, applied to the co-stardom network:

- If an actor had not been in the same sub-network, his/her Bacon number is 0.
- Those actors who have worked directly with Kevin Bacon have a Bacon number of 1.
- If the lowest Bacon number of any actor with whom X has appeared in any movie is N, X's Bacon number is N+1.

## How Does Algorithm Work?

- This algorithm is written in C Language.
- Actor - Movie data is in ../data directory.
- Input format is in:
    
    Movie1(year)/surname_actor1, name_actor1/surname_actor2, name_actor2
    
    Movie2(year)/surname_actor3, name_actor3/surname_actor4, name_actor4
    
- String tokenizer is used for cleaning the data.
- Algorithm converts data into Undirected Bipartite Graph after find that what is the Vertex number of this graph.
- After graph is made, Breadth First Search is used for finding what is Bacon number of every single actor.
- Breadth First Search is also used for what is the shortest connection map distance between a specific actor and Kevin Bacon.

## Run
```bash
chmod 777 run.sh
./run.sh
```
<img src="https://media.giphy.com/media/vFKqnCdLPNOKc/giphy.gif" width="40" height="40" />


## References 
- https://en.wikipedia.org/wiki/Six_Degrees_of_Kevin_Bacon
