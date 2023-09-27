import React, { useContext, useState } from "react";

import Box from "@mui/material/Box";
import TextField from "@mui/material/TextField";
import Button from "@mui/material/Button";
import Typography from "@mui/material/Typography";
import { StatusContext } from "../contexts/StatusContext";
import { setWifi } from "../services/configService";

export default function Wifi() {
  const [status] = useContext(StatusContext);
  const [ssid, setSSID] = useState(status.config.wifi.ssid);
  const [password, setPassword] = useState("");

  const onSave = () => {
    setWifi(ssid, password);
  };

  return (
    <Box component="form">
      <Typography variant="h4">Wifi</Typography>
      <TextField
        label="SSID"
        variant="filled"
        fullWidth
        value={ssid}
        onChange={(event) => setSSID(event.target.value)}
      />
      <TextField
        label="Password"
        variant="filled"
        type="password"
        fullWidth
        value={password}
        onChange={(event) => setPassword(event.target.value)}
      />
      <Button variant="contained" fullWidth onClick={() => onSave()}>
        Save
      </Button>
    </Box>
  );
}
