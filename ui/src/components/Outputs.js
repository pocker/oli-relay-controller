import React, { useContext } from "react";

import List from "@mui/material/List";
import ListItem from "@mui/material/ListItem";
import ListItemIcon from "@mui/material/ListItemIcon";
import ListItemText from "@mui/material/ListItemText";
import ListSubheader from "@mui/material/ListSubheader";
import Switch from "@mui/material/Switch";

import OutputIcon from '@mui/icons-material/Output';
import { StatusContext } from "../contexts/StatusContext";

export default function Outputs() {
  const [status] = useContext(StatusContext);
  const {
    K_1,
    K_2,
    K_3,
  } = status.outputs;
  return (
    <List subheader={<ListSubheader>Outputs</ListSubheader>}>
      <ListItem>
        <ListItemIcon>
          <OutputIcon color="red[500]" />
        </ListItemIcon>
        <ListItemText primary="K_1" />
        <Switch edge="end" disabled checked={K_1} />
      </ListItem>
      <ListItem>
        <ListItemIcon>
          <OutputIcon />
        </ListItemIcon>
        <ListItemText primary="K_2" />
        <Switch edge="end" disabled checked={K_2} />
      </ListItem>
      <ListItem>
        <ListItemIcon>
          <OutputIcon />
        </ListItemIcon>
        <ListItemText primary="K_3" />
        <Switch edge="end" disabled checked={K_3} />
      </ListItem>
    </List>
  );
}
