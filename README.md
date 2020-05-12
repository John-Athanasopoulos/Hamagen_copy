# Data Struct Assignment: Hamagen Copy

*Defending against Corona Virus!*

<hr>
With the recent **Covid-19** Outbreak, we had an assignment form our Universitry about a program similar to Hamagen, that:


    1. Tracks the daily trajectory of some virtual users of the application (10 users, that are randomly healthy or not).
      
    2. Checks the trajectories and checks for any possible new Covid-19 patients.
      
    3. Checks for any regions that the users tend to visit often and stay for a minimum time.
    
    4. Repairs any GPS signals that got lost in the trajectory of the user.
    
    5. After some days Summarize the trajectory of a user for a previous day, so that it doesn't occupy space without reason.

Keep in mind that this simulation runs for a **60x60 grid** (starting to count from 0), the users move every **30 seconds**. The users move based on a variation of the **Random Waypoint Model**, where they move for a portion of the 30 seconds and afterwards stop until the 30 second mark, while keeping a speed of 3-6 units/s. The grid is 60x60 so that even for the biggest distance (two diagonal corners) and the lowest speed (3 units/s), the user will manage to arrive to the destination before the 30 second mark, and specifically at 28.3 seconds ([60 * 2^1/2]/3 = 28.3 seconds approximately).

<hr>

Hope you like it! You can play around with the values so that you get the results of your own simulation.
