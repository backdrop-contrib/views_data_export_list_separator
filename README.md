# Views Data Export List Separator (for CSVs)

This module changes ordered/unordered values in a multi-value field
into a simple comma, newline, etc., when you create a Data Export display as a CSV.
You do not need to manually override the field's display values.

For example, if your normal page view uses a table and has columns that look like this:

| Date    | Friends |
|--- 	  |---	    |
|1/1/2026 | - Jeff  |
|         | - Sally |
|         | - Ralf  |
|---	  |---      |
|1/6/2026 | - Bill  |
|         | - June  |


And you then create a Views Data Export as a CSV, you can change the format settings
to convert the list elements into a simple comma-separated list, without having to
override how the multi-value field is displayed.

Ex:

```
"Date","Friends"
"1/1/2026","Jeff, Sally, Ralf"
"1/6/2026","Bill, June"
```

## Why do I need this?

If you use the Views module to create "reports" for your users, and in addition
to giving them an attractive, filterable view in the browser, you also give them
the ability to export the report as a CSV file, this module may be for you.


## Help and Setup

Create your view normally, and add a Data Export display.

Select the **CSV file** format, and open
its settings. The module adds the following options towards the bottom of the form:

- **Convert ordered and unordered lists to separated values.** Enable this to
  convert `<ul>` and `<ol>` field output in this CSV export.

- **List-item separator.** The default is a comma. Enter any text to use it
  between items, such as `, ` or `; `. Enter `\n` to use a newline.

Existing CSV exports are unchanged until this behavior is enabled. The source
display's field formatter is never changed, so it may continue rendering list
markup for browser output.



## Roadmap

- Add this same functionality to XLS exports as well as CSV.


## Current Maintainers

- [Richard Peacock](https://github.com/swampopus)
- Seeking additional maintainers.

## Credits

- Created for Backdrop CMS by [Richard Peacock](https://github.com/swampopus)
- Developed with AI assistance


## License

This project is GPL v2 software.
