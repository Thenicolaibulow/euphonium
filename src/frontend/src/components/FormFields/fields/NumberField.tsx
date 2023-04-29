

import { useDispatch, useSelector } from "react-redux";
import { ConfigurationNumberField } from "../../../api/euphonium/plugins/models";
import { onFieldChanged, pluginStateSelector } from "../../../redux/reducers/pluginConfigurationsReducer";
import Input from "../../ui/Input";
import { FieldProps } from "./FieldProps";

export default function NumberField({ field, pluginName }: FieldProps<ConfigurationNumberField >) {
  const pluginState = useSelector(pluginStateSelector(pluginName));
  const dispatch = useDispatch();
  return (
    <Input
      type="number"
      tooltip={field.label}
      value={pluginState[field.stateKey]}
      width={90}
      onChange={(str) => dispatch(onFieldChanged({
        pluginName,
        key: field.stateKey,
        value: parseFloat(str),
        debounce: true
      }) as any)}
      onBlur={() => dispatch(onFieldChanged({
        pluginName,
        key: field.stateKey,
        value: pluginState[field.stateKey],
        debounce: false
      }) as any)}
    />
  );
}
