/*
  Linear search designed to solve more than just the first constraint
*/
int tryCombination(int switch_positions[]);
void answer(int switch_positions[], int door_for_switch[]);

void set_a_switch(int door, int switch_positions[], int door_for_switch[],
                  int n) {
  int i, result;
  int found = 0;

  for (i = 0; i < n; i++)
    if (door_for_switch[i] == -1)
      switch_positions[i] = 0;

  result = tryCombination(switch_positions);
  if (result != door) {
    // door is open - we'll want to close it to know which idx opens it
    for (i = 0; i < n; i++)
      // set all unassociated switches to 1
      // this is guaranteed to close the open door since
      // we don't know what switch it's tied to
      if (door_for_switch[i] == -1)
        switch_positions[i] = 1;
  }

  i = 0;
  while (!found) {
    if (door_for_switch[i] == -1) {
      // set switch to opposite position
      switch_positions[i] = 1 - switch_positions[i];
      result = tryCombination(switch_positions);
      if (result != door)
        found = 1;
      else
        i++;
    } else
      i++;
  }
  door_for_switch[i] = door;
}

void exploreCave(int n) {
  int switch_positions[n], door_for_switch[n];
  int i;
  for (i = 0; i < n; i++)
    door_for_switch[i] = -1;
  for (i = 0; i < n; i++)
    set_a_switch(i, switch_positions, door_for_switch, n);
  answer(switch_positions, door_for_switch);
}