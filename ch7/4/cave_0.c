/*

discovered secret cave
- entrance blocked by security system of N consecutive doors and N switches
  - each door is behind the previous
  - each switch is connected to a different door
- doors numbered 0 -> n - 1
  - door 0 is closest to you
- switches have either up(0) or down(1) position
- one of the switches positions is correct for each door, but you don't know
which
- you don't know which switch is connected to which door
- you have 70_000 attempts at opening every door using the procedure
exploreCave()

---

Apparently, "we wanna use binary search to quickly zone in on a desired
element". Could that be related to honing in to which switch controls which
door? I'm thinking that's where the author is going, but not sure.

*/
