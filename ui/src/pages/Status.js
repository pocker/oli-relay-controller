import React from "react";

import Grid from "@mui/material/Unstable_Grid2";
import Inputs from "../components/Inputs";
import Outputs from "../components/Outputs";
import ProfileSelector from "../components/ProfileSelector";

export default function Status() {
  return (
    <Grid container justifyContent="center" spacing={1}>
       <Grid item xs={12}>
        <ProfileSelector />
      </Grid>
      <Grid item xs={12} md={3}>
        <Inputs />
      </Grid>
      <Grid item xs={12} md={3}>
        <Outputs />
      </Grid>
    </Grid>
  );
}
