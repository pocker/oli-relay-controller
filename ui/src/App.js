import React, { useState } from "react";

import Grid from "@mui/material/Grid";
import Tabs from "@mui/material/Tabs";
import Tab from "@mui/material/Tab";
import { ThemeProvider, createTheme } from "@mui/material/styles";
import CssBaseline from "@mui/material/CssBaseline";

import Status from "./pages/Status";
import Config from "./pages/Config";
import StatusContextProvider from "./contexts/StatusContext";

const darkTheme = createTheme({
  palette: {
    mode: "dark",
  },
});

export default function App() {
  const [tab, setTab] = useState(0);

  const handleTabCahnge = (_, index) => setTab(index);

  return (
    <ThemeProvider theme={darkTheme}>
      <CssBaseline />
      <Grid container paddingTop={2} justifyContent="center">
        <Grid item xs={8}>
          <Tabs
            value={tab}
            onChange={handleTabCahnge}
            sx={{ borderRight: 1, borderColor: "divider" }}
          >
            <Tab label="Status" />
            <Tab label="Config" />
          </Tabs>
          <StatusContextProvider>
            {tab === 0 && <Status />}
            {tab === 1 && <Config />}
          </StatusContextProvider>
        </Grid>
      </Grid>
    </ThemeProvider>
  );
}
