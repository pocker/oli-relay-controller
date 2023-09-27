import React from "react";

import Box from "@mui/material/Box";
import Button from "@mui/material/Button";
import Typography from "@mui/material/Typography";

export default function Misc() {
  const restart = () => fetch("/restart");
  return (
    <Box component="form">
      <Typography variant="h4">Misc</Typography>
      <Button
        variant="contained"
        color="error"
        fullWidth
        onClick={() => restart()}
      >
        Reboot
      </Button>
    </Box>
  );
}
