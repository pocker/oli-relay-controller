import React, { useContext, useEffect, useState } from "react";

import Table from "@mui/material/Table";
import TableBody from "@mui/material/TableBody";
import TableCell from "@mui/material/TableCell";
import TableContainer from "@mui/material/TableContainer";
import TableHead from "@mui/material/TableHead";
import TableRow from "@mui/material/TableRow";
import MenuItem from "@mui/material/MenuItem";
import Select from "@mui/material/Select";
import FormControl from "@mui/material/FormControl";
import InputLabel from "@mui/material/InputLabel";

import { StatusContext } from "../contexts/StatusContext";
import { Button, ButtonGroup, Container } from "@mui/material";
import { setConfig } from "../services/configService";

function decodeConfig(config) {
  return config.map((value) => [0, 2, 4].map((shift) => (value >> shift) & 3));
}

function encodeConfig(config) {
  return config.map((row) =>
    row.reduce((prev, curr, index) => prev | ((curr & 3) << (index * 2)), 0)
  );
}

export default function Profile() {
  const [status, refresh] = useContext(StatusContext);
  const [active, setActive] = useState(status.config.profile.active);
  const [configuration, setConfiguration] = useState([]);

  const onConfigUpdate = (i, j, v) => {
    const newConfig = [...configuration];
    newConfig[i][j] = v;
    setConfiguration(newConfig);
  };

  const onReset = () => {
    setConfiguration(decodeConfig(status.config.profile.configuration[active]));
  };

  const onSave = () => {
    const newConfig = encodeConfig(configuration);
    const newProfile = [...status.config.profile.configuration];
    newProfile[active] = newConfig;
    setConfig(newProfile);
  };

  useEffect(onReset, [active]);

  return (
    <Container>
      <TableContainer>
        <Table>
          <TableHead>
            <TableRow>
              <TableCell>T1</TableCell>
              <TableCell>T2</TableCell>
              <TableCell>T3</TableCell>
              <TableCell>
                <FormControl>
                  <InputLabel>Profile</InputLabel>
                  <Select
                    label="Profile"
                    value={active}
                    onChange={(event) => setActive(event.target.value)}
                  >
                    <MenuItem value={0}>1</MenuItem>
                    <MenuItem value={1}>2</MenuItem>
                  </Select>
                </FormControl>
              </TableCell>
            </TableRow>
          </TableHead>
          <TableBody>
            {configuration.map((row, i) => (
              <TableRow>
                {row.map((value, j) => (
                  <TableCell>
                    <Select
                      key={`${i}_${j}`}
                      value={value}
                      onChange={(event) =>
                        onConfigUpdate(i, j, event.target.value)
                      }
                    >
                      <MenuItem disabled value={0}>
                        N/A
                      </MenuItem>
                      <MenuItem value={1}>OFF</MenuItem>
                      <MenuItem value={2}>ON</MenuItem>
                      <MenuItem value={3}>?</MenuItem>
                    </Select>
                  </TableCell>
                ))}
                <TableCell color="success">K{i + 1}</TableCell>
              </TableRow>
            ))}
          </TableBody>
        </Table>
      </TableContainer>
      <Container>
        <ButtonGroup>
          <Button variant="contained" color="success" onClick={() => onSave()}>
            Save
          </Button>
          <Button variant="outlined" color="error" onClick={() => onReset()}>
            Reset
          </Button>
        </ButtonGroup>
      </Container>
    </Container>
  );
}
