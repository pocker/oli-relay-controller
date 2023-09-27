import React from "react";

import Grid from "@mui/material/Unstable_Grid2";

import Wifi from "../components/Wifi";
import User from "../components/User";
import Misc from "../components/Misc";
import Updater from "../components/Updater";
import Profile from "../components/Profile";

export default function Config() {
  return (
    <Grid container justifyContent="center" spacing={3}>
      <Grid item sm={12} md={6}>
        <Wifi />
      </Grid>
      <Grid item sm={12} md={6}>
        <User />
      </Grid>
      <Grid item sm={12} md={6}>
        <Updater />
      </Grid>
      <Grid item sm={12} md={6}>
        <Misc />
      </Grid>
      <Grid item sm={12}>
        <Profile />
      </Grid>
    </Grid>
  );
}
