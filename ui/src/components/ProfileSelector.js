import React, { useContext } from "react";

import { StatusContext } from "../contexts/StatusContext";
import { Box, Button, ButtonGroup } from "@mui/material";
import { setActiveProfile } from "../services/configService";

export default function ProfileSelector() {
  const [status] = useContext(StatusContext);

  const updateProfile = (id) => {
    setActiveProfile(id).then(() => setActive(id));
  };

  return (
    <Box
      display="flex"
      flexDirection="column"
      alignItems="center"
      justifyContent="center"
    >
      <ButtonGroup justifyContent="center">
        <Button
          variant={status.config.profile.active == 0 ? "contained" : "outlined"}
          color="primary"
          size="medium"
          onClick={() => updateProfile(0)}
        >
          Profile 1
        </Button>
        <Button
          variant={status.config.profile.active == 1 ? "contained" : "outlined"}
          color="primary"
          size="medium"
          onClick={() => updateProfile(1)}
        >
          Profile 2
        </Button>
      </ButtonGroup>
    </Box>
  );
}
