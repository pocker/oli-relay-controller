import React, { useState } from "react";

import Box from "@mui/material/Box";
import TextField from "@mui/material/TextField";
import Button from "@mui/material/Button";
import Typography from "@mui/material/Typography";

export default function Updater() {
  const [firmware, setFirmware] = useState();

  const onFimrwareSelect = (event) => {
    if (event.target.files) {
      setFirmware(event.target.files[0]);
    }
  };

  const upoloadFirmware = () => {
    const formData = new FormData();
    formData.append(firmware.name, firmware);

    fetch("/update", {
      method: "POST",
      body: formData,
    })
      .then(() => window.location.reload(false))
      .catch((err) => alert(err));
  };

  return (
    <Box component="form">
      <Typography variant="h4">Updater</Typography>
      <TextField
        label="Firmware"
        variant="filled"
        fullWidth
        type="file"
        onChange={(event) => onFimrwareSelect(event)}
      />
      <Button
        variant="contained"
        disabled={!firmware}
        fullWidth
        onClick={() => upoloadFirmware()}
      >
        Upload
      </Button>
    </Box>
  );
}
