import React, { useContext } from "react";

import List from "@mui/material/List";
import ListItem from "@mui/material/ListItem";
import ListItemIcon from "@mui/material/ListItemIcon";
import ListItemText from "@mui/material/ListItemText";
import ListSubheader from "@mui/material/ListSubheader";
import Switch from "@mui/material/Switch";

import { StatusContext } from "../contexts/StatusContext";
import InputIcon from "@mui/icons-material/Input";

export default function Inputs() {
  const [status] = useContext(StatusContext);
  const { T_1, T_2, T_3 } = status.inputs;
  return (
    <List subheader={<ListSubheader>Inputs</ListSubheader>}>
      <ListItem>
        <ListItemIcon>
          <InputIcon />
        </ListItemIcon>
        <ListItemText primary="T_1" />
        <Switch edge="end" disabled checked={T_1 === 2} />
      </ListItem>
      <ListItem>
        <ListItemIcon>
          <InputIcon />
        </ListItemIcon>
        <ListItemText primary="T_2" />
        <Switch edge="end" disabled checked={T_2 === 2} />
      </ListItem>
      <ListItem>
        <ListItemIcon>
          <InputIcon />
        </ListItemIcon>
        <ListItemText primary="T_3" />
        <Switch edge="end" disabled checked={T_3 === 2} />
      </ListItem>
    </List>
  );
}
