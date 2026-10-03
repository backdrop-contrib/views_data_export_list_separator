# Views Data Export List Separator (for CSVs)

This module changes ordered/unordered values in a multi-value field
into a simple comma, newline, etc., when you create a Data Export display as a CSV.
You do not need to manually override any field values.

For example, if your normal page view uses a table and has columns that look like this:

| Date    | Friends |
|-------- |---------|
|1/1/2026 | - Jeff  |
|         | - Sally |
|         | - Ralf  |
|---------|---------|
|1/6/2026 | - Bill  |
|         | - June  |
|---------|---------|

And you then create a Views Data Export as a CSV, you can change the format settings
to convert the list elements into a simple comma-separated list, without having to
override how the multi-value field is displayed.

Ex:

```
"Date","Friends"
"1/1/2026","Jeff, Sally, Ralf"
"1/6/2026","Bill, June"
```


# Help and Setup

Create your view normally, and add a Data Export display.

Select the **CSV file** format, and open
its settings. The module adds the following options towards the bottom of the form:

- **Convert ordered and unordered lists to separated values.** Enable this to
  convert `<ul>` and `<ol>` field output in this CSV export.

- **List-item separator.** The default is a comma. Enter any text to use it
  between items, such as `, ` or `; `. Enter `\n` to use a newline.

Existing CSV exports are unchanged until the checkbox is enabled. The source
display's field formatter is never changed, so it may continue rendering list
markup for browser output.

**Example:** A field rendered as `<ul><li>Alpha</li><li>Bravo</li></ul>` is
exported as `Alpha,Bravo` with the default separator, or as two lines when
the separator is `\n`.


## Current Maintainers

- [Richard Peacock](https://github.com/swampopus)
- Seeking additional maintainers.

## Credits

- Created for Backdrop CMS by [Richard Peacock](https://github.com/swampopus)
- Developed with AI assistance


## License

This project is GPL v2 software.