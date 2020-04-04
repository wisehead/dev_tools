with 子句使您可以详细而精确地指定线的样式。在本例中，我们说明两种有用的样式。第一种样式 linespoints 通常在对数据绘图时非常有用，它在涉及的每个示例或数据点处标记一个点，并使用线性插值法连接连续的点。这里我们另外指定点类型为 5，它选择终端允许的第五种点。第二种样式 boxes 更适合绘制直方图数据。注意我们如何在 cos(x) 曲线中将 with 缩写成 w。类似地，lt 是 linetype 的缩写，是另一个特定于终端的设置，它选择终端可以绘制的四种线。不必说，您可以使用 pt 代替冗长的 pointtype。如果想在多条线中使用相同的绘图样式（在一个 plot 命令中或在多个 plot 命令中），可以使用 set 命令设置绘图样式：set style function linespoints。要更改用于绘制与函数相对的数据集合的样式，使用 set style data linespoints。

当绘制两条或多条曲线时，我们需要关键字或图例来对它们进行区分。默认情况下，关键字在右上角；但是如果它妨碍了图，可以将关键字放到其他位置 。如果愿意，甚至可以放到图外。