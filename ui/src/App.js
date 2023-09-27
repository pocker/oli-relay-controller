import React, { useState } from "react";

import Grid from "@mui/material/Grid";
import { ThemeProvider, createTheme } from "@mui/material/styles";
import CssBaseline from "@mui/material/CssBaseline";

import Status from "./pages/Status";
import Config from "./pages/Config";
import StatusContextProvider from "./contexts/StatusContext";
import {
  AppBar,
  Container,
  Tab,
  Tabs,
  Toolbar,
  Typography,
} from "@mui/material";

const darkTheme = createTheme({
  palette: {
    mode: "dark",
  },
});

const pages = [
  { name: "Status", component: Status },
  { name: "Config", component: Config },
];

export default function App() {
  const [tab, setTab] = useState(0);
  const handleTabChange = (_, index) => setTab(index);
  const ActivePage = pages[tab].component;

  return (
    <ThemeProvider theme={darkTheme}>
      <CssBaseline />
      <AppBar position="sticky">
        <Toolbar>
          <Typography style={{ marginRight: "15px" }}>
            RelayController
          </Typography>
          <Tabs onChange={handleTabChange} value={tab}>
            {pages.map((page, index) => (
              <Tab label={page.name} value={index} />
            ))}
          </Tabs>
        </Toolbar>
      </AppBar>
      <Container style={{ marginTop: "15px" }}>
        <StatusContextProvider>
          <ActivePage />
        </StatusContextProvider>
      </Container>
    </ThemeProvider>
  );
}
